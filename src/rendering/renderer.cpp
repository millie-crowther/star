#include "rendering/renderer.h"
#include <glm/glm.hpp>
#include <iostream>
#include "utils/resources.h"

const struct {
    float x, y;
} vertices[6]{
    { -1.0f, -1.0f },
    {  1.0f, -1.0f },
    { -1.0f,  1.0f },
    { -1.0f,  1.0f },
    {  1.0f,  1.0f },
    {  1.0f, -1.0f }
};

const char * vertex_shader_text = "attribute vec2 p; void main(){gl_Position=vec4(p,0,1);}";

static renderer_t * INSTANCE = nullptr;

/*
 *  static callback function for GLFW
 */
//TODO: refactor
static void
window_size_callback(GLFWwindow * window, int width, int height){
    if (INSTANCE != nullptr){
        INSTANCE->update_window_size(width, height);
    }
}

void
renderer_t::update_window_size(int width, int height){
    this->width = width;
    this->height = height;

    GLint loc = glGetUniformLocation(program, "window_size");
    if (loc != -1){
        glUniform2f(loc, (GLfloat) width, (GLfloat) height);
    }
}

renderer_t::renderer_t(){
    INSTANCE = this;
    main_camera = nullptr;
    window = nullptr;
}

bool
renderer_t::initialise(GLFWwindow * window){
    this->window = window;
    if (window == nullptr){
        return false;
    }    
 
    //set up vertex buffer
    GLuint vertex_buffer;

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //compile vertex shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    //compile fragment shader
    std::string shaderstr = resources::readTextFile("Shaders/fragment_shader.glsl");
    const char * shader = shaderstr.c_str();
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &shader, NULL);
    glCompileShader(fragment_shader);

    GLint isCompiled = 0;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &isCompiled);
       
    GLint maxLength = 0;
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    char * errorLog = new char[maxLength];
    glGetShaderInfoLog(fragment_shader, maxLength, &maxLength, errorLog);

    std::cout << "output from compiling fragment shader: " << std::endl;
    std::cout << errorLog << std::endl;
    
    if (isCompiled == GL_FALSE){
        glDeleteShader(fragment_shader); // Don't leak the shader.
        return false;
    }

    //create and link program
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program); 

    //set vertex attributes
    GLint vpos_location = glGetAttribLocation(program, "p");
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*) 0);

    //set uniform on shader
    glUseProgram(program);
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    update_window_size(w, h);

    glm::vec3 up(0.0, 1.0, 0.0);
    GLint loc = glGetUniformLocation(program, "camera_up");
    glUniform3f(loc, up[0], up[1], up[2]);

    glm::vec3 right(1.0, 0.0, 0.0);
    loc = glGetUniformLocation(program, "camera_right");
    glUniform3f(loc, right[0], right[1], right[2]);

    glfwSetWindowSizeCallback(window, window_size_callback);

    // create ssbo
    glGenBuffers(1, &octree_ssbo);
    return true;
}

void
renderer_t::set_main_camera(camera_t * camera){
    main_camera = camera; 
}

void
renderer_t::draw(){
    glUseProgram(program);
    glViewport(0, 0, width, height);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

bool
renderer_t::is_visible(bounds_t bounds){
    //TODO
    return true;
}

bool 
renderer_t::is_terminal(bounds_t bounds){
    return bounds.volume() == 1;
}

void
renderer_t::upload_octree_data(std::vector<int> * data){
    data->insert(data->begin(), data->size());
    
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, octree_ssbo); 
    glBufferData(
	GL_SHADER_STORAGE_BUFFER, 
	sizeof(int) * data->size(), 
	&(data->at(0)), 
	GL_DYNAMIC_DRAW
    );
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, octree_ssbo);

    data->erase(data->begin());
}
