//
// Created by Edward Hyde on 16/11/2018.
//

#ifdef __APPLE__
#include "gl3w.h"
#define GLFW_NO_GLU 1
#include "GLFW/glfw3.h"
#endif

#include <cstdio>
#include <cstring>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <sstream>

GLuint loadShaders(){

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string vertexShaderCode = "#version 330 core\n"
                                   "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
                                   "void main(){\n"
                                   "    gl_Position.xyz = vertexPosition_modelspace;\n"
                                   "    gl_Position.w = 1.0;\n"
                                   " }";

    std::string fragmentShaderCode = "#version 330 core\n"
                                     "out vec3 color;\n"
                                     "\n"
                                     "void main(){\n"
                                     "    color = vec3(1,0,0);\n"
                                     "}";

    GLint Result = GL_FALSE;
    int logLength;

    char const * vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertexSourcePointer , nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0){
        std::vector<char> errorMessage(logLength+1);
        glGetShaderInfoLog(vertexShader, logLength, nullptr, &errorMessage[0]);
        fprintf(stdout, "%sn", &errorMessage[0]);
    }

    char const * fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourcePointer , nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0){
        std::vector<char> errorMessage(logLength+1);
        glGetShaderInfoLog(fragmentShader, logLength, nullptr, &errorMessage[0]);
        fprintf(stdout, "%s\n", &errorMessage[0]);
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &Result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0){
        std::vector<char> errorMessage(logLength+1);
        glGetProgramInfoLog(program, logLength, nullptr, &errorMessage[0]);
        fprintf(stdout, "%s\n", &errorMessage[0]);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}


void error_callback(int error, const char* description) {
    puts(description);
}

int main(){
    if( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(error_callback);
    GLFWwindow* window;
    window = glfwCreateWindow( 1024, 768, "Triangle", nullptr, nullptr);
    if( window == nullptr ){
        fprintf( stderr, "Can not open OpenGL window\n" );
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gl3wInit();
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
    };
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    GLuint program = loadShaders();

    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
}