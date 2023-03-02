//
//  main.cpp
//  HelloTriangleExcercise2
//
//  Created by Sasidharan Mahalingam on 3/1/23.
//

#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>

// framebuffer size function to resize the viewport everytime the use resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// input function that gets triggered every time a input key is pressed
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, const char * argv[]) {
    // set up GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // create a GFLW Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // set up viewport size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // set up GLAD to manage OpenGL function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // define the vertex shader
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n "
    "void main()\n"
    "{\n"
    "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    
    // define the fragment shader
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "}\0";
    
    // compile vertex shaders
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check if the vertex shader compiled successfully
    int success;
    char infoLog[1024];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check if the fragment shader compiled successfully
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // link compiled shaders to a shader program object
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check if the shader program compiled successfully
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // define the triangle vertices
    float firstTriangleVertices[] = {
        // first triangle
        -0.9f,  -0.5f, 0.0f,
        0.0f,  -0.5f, 0.0f,
        -0.45f,  0.5f, 0.0f,
    };
    float secondTriangleVertices[] = {
        // second triangle
         0.0f,  -0.5f, 0.0f,
         0.9f,  -0.5f, 0.0f,
         0.45f,  0.5f, 0.0f
    };
    // defining VBOs and VAOs
    unsigned int VBO[2], VAO[2];
    glGenVertexArrays(2, &VAO[0]);
    glGenBuffers(2, &VBO[0]);
    // bind the first VAO and VBO
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    
    //copy data into the bound VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangleVertices), firstTriangleVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //unbind VAO
    glBindVertexArray(0);
    
    // vind the second VAO and VBO
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    
    //copy data into the bound VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangleVertices), secondTriangleVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //unbind VAO
    glBindVertexArray(0);
    
    
    // start render loop
    while(!glfwWindowShouldClose(window))
    {
        // process any inputs
        processInput(window);
        
        // rendering commands
        // clear color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // draw the first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        // draw the second triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        // poll events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    // deallocate all resources
    glDeleteVertexArrays(2, &VAO[0]);
    glDeleteBuffers(2, &VBO[0]);
    
    // delete shaders
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // terminate GLFW's resources
    glfwTerminate();
    
    return 0;
}
