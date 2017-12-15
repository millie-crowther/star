#include "engine.h"
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "utils/resources.h"

static engine_t * INSTANCE = nullptr;

/*
 *  static callback functions for GLFW
 */

static void
window_size_callback(GLFWwindow * window, int width, int height){
    if (INSTANCE != nullptr){
    	INSTANCE->update_window_size(width, height);
    }
}

void
engine_t::update_window_size(int width, int height){
    GLint loc = glGetUniformLocation(program, "window_size");
    if (loc != -1){
        glUniform2f(loc, (GLfloat) width, (GLfloat) height);
    } 
}

std::string
engine_t::get_fragment_shader(){
    return resources::readTextFile("Shaders/fragment_shader.glsl");    
}

bool 
engine_t::initialise(){
    INSTANCE = this;

    const struct
    {
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

    if (!glfwInit()){
        std::cout << "Failed to initialise GLFW" << std::endl;
        return false;
    }

    int window_width = 320;
    int window_height = 240;

    window = glfwCreateWindow(window_width, window_height, "hello world!", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return false;
    }

    input.set_window(window);    
    renderer.set_window(window);

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, window_size_callback);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

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
    std::string shaderstr = get_fragment_shader();
    const char * shader = shaderstr.c_str();
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &shader, NULL);
    glCompileShader(fragment_shader);

    GLint isCompiled = 0;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){
	GLint maxLength = 0;
	glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);

	// The maxLength includes the NULL character
	char * errorLog = new char[maxLength];
	glGetShaderInfoLog(fragment_shader, maxLength, &maxLength, errorLog);

	// Exit with failure.
	glDeleteShader(fragment_shader); // Don't leak the shader.
	
        std::cout << "Failed to compile fragment shader" << std::endl;
        std::cout << errorLog << std::endl;
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
    GLint loc = glGetUniformLocation(program, "window_size");
    glUniform2f(loc, (GLfloat) window_width, (GLfloat) window_height);

    glm::vec3 up(0.0, 1.0, 0.0);
    loc = glGetUniformLocation(program, "camera_up");
    glUniform3f(loc, up[0], up[1], up[2]);
    
    glm::vec3 right(1.0, 0.0, 0.0);
    loc = glGetUniformLocation(program, "camera_right");
    glUniform3f(loc, right[0], right[1], right[2]);

    
    return true;
}

void
engine_t::terminate(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void
engine_t::draw(){
    glUseProgram(program);
	
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void
engine_t::update(double delta){
    if (input.is_key_pressed(GLFW_KEY_ESCAPE)){ 
	glfwSetWindowShouldClose(window, GL_TRUE);
    }

    theta -= input.get_mouse_velocity().x / 10000000.0;
    glm::vec3 right(cos(theta), 0.0, sin(theta));
    GLint loc = glGetUniformLocation(program, "camera_right");
    glUniform3f(loc, right[0], right[1], right[2]);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void
engine_t::run(){
    double time = glfwGetTime();
    while (!glfwWindowShouldClose(window)){
        double delta =  glfwGetTime() - time;
	time = glfwGetTime();
        
        double fps = 1.0 / delta;
	std::string title = "FPS: " + std::to_string(fps);
	glfwSetWindowTitle(window, title.c_str());

	update(delta);
	draw();
    }
}
