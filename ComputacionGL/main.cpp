#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <windows.h>

#include "Shaders/Shader.h"
#include "Shaders/ShaderProgram.h"

int alternativeColorLocation;
float vertices[] = {
        
    -0.6f, 0.1f, 0.0f,//A 0
    -0.5f, 0.3f, 0.0f,//B 1
    -0.2f, 0.5f, 0.0f,//C 2
    0.2f, 0.5f, 0.0f, //D 3
    0.5f, 0.3f, 0.0f, //E 4
    0.6f, 0.1f, 0.0f, //F 5
    0.0f, -0.2f, 0.0f,//G 6 //Morro
    -0.5f, 0.6f, 0.0f,//H 7
    0.5f, 0.6f, 0.0f, //I 8
    -0.2f, 0.1f, 0.0f,//J 9
    0.2f, 0.1f, 0.0f, //K 10
    -0.3f, 0.0f, 0.0f,//L 11
    0.3f, 0.0f, 0.0f, //M 12

    -0.11f,0.2f,0.0f, //N 13
    0.11f,0.2f,0.0f, //O 14

    -0.08f,0.1f,0.0f, //P 15
    0.08f,0.1f,0.0f    //Q 16
};

unsigned int indices[] = {
    7,1,2, //ORELLA E
    3,8,4,
    0,1,11, //GALTA
    5,4,12,
    11,6,9,
    6,10,12,

    1,2,9,
    3,4,10,

    1,11,9,
    10,4,12,

    2,3,6,
    2,9,13,
    3,10,14,

    2,9,13,
    9,15,6,

    3,14,10,
    10,16,6
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

float colores[] =
{
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.5f, 1.5f, 1.0f
};
void Draw(int& i, int& j)
{
    glUniform4f(alternativeColorLocation, colores[i+0], colores[i+1], colores[i+2], colores[i+3]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (int*)NULL + (3 * j));
    i=i+4;
    if (i>=16)
        i=0;
}

int main(void)
{
   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Computacion Grafica", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader* MyShader = new Shader();
    unsigned int shaderProgram = ShaderProgram().CreateAttachAndLinkShaderProgram(MyShader->vertexShader, MyShader->fragmentShader);
    
    alternativeColorLocation = glGetUniformLocation(shaderProgram, "alternativeColor");
    
    unsigned int VBO; //VertexBufferObject (VBO)
    unsigned int VAO; //VertexAttributeObject
    unsigned int IBO; //Index buffer object

    //Generem els IDs
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);
    //Bindear Buffer

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Triangles
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(0);
    
    //Unbindear Buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   
    
    int i = 0;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.9f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
///---------------------------------
        // for (unsigned int i = 0; i < sizeof(indices) / sizeof(indices[0]) / 3; i++) {
        //     glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * i * sizeof(GLuint)));
        // }
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
///---------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
    glfwTerminate();

    return 0;
}
