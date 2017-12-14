#include "engine.h"
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "utils/resources.h"

static void 
key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

std::string
engine_t::get_fragment_shader(){
    return resources::readTextFile("Shaders/fragment_shader.glsl");    
}

bool 
engine_t::initialise(){
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

    window = glfwCreateWindow(640, 480, "hello world!", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
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

    return true;
}

void
engine_t::terminate(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void
engine_t::draw(){
    float ratio;
    int width, height;
    
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void
engine_t::update(double delta){
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    GLint loc = glGetUniformLocation(program, "window_size");
    if (loc != -1){
        glUniform2f(loc, (GLfloat) width, (GLfloat) height);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void
engine_t::run(){
    double time = glfwGetTime();
    while (!glfwWindowShouldClose(window)){
        update(1.0);
        draw();
    }
}
