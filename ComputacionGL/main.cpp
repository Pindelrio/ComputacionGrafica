#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// #include "Shaders/Shader.h"
// #include "Shaders/ShaderProgram.h"
#include <STB/stb_image.h>

int customColor;
float vertices[] = {
    //Coordenades      //Color            //Textura
    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //Top Left
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //Down Left
     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //Down Right
     0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, //Top Right
};

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;  \n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aText; \n"
"                                     \n"
"out vec3 ourColor;                   \n"
"out vec2 textCoord;                  \n"
"                                     \n"
"void main()                          \n"
"{                                    \n"
"    gl_Position = vec4(aPos, 1.0);   \n"
"    ourColor = aColor;               \n"
"    textCoord = aText;               \n"
"}                                    \n\0";

const char* fragmentShaderSource =
"#version 330 core                            \n"
"out vec4 FragColor;                          \n"
"in vec3 ourColor;                            \n"
"in vec2 textCoord;                            \n"
"uniform sampler2D u_texture;                 \n"
"void main()                                  \n"
"{                                            \n"
"    FragColor = texture(u_texture, textCoord);\n"
"}                                            \n\0";

unsigned int indices[] = {
    0,1,2,
    0,2,3
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
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

    //GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    //customColor = glGetUniformLocation(shaderProgram, "ourColor");
    
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

    unsigned int stride = 8 * sizeof(float);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    //Unbindear Buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   
    //TEXTURAS
    //------------------------------------------------------------------------------------------------------------------
    int widthImg, heighImg, PixelNum;

    //stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load("Image.jpg", &widthImg, &heighImg, &PixelNum, 0);

    GLuint textureID;
    glGenTextures(1, &textureID); //numero de textures
    glBindTexture(GL_TEXTURE_2D, textureID);

    //Com es comporta el suavitzat de entre pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heighImg, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    else
    {
        std::cout << "Failed to load image" << std::endl;
    }
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0); //Evitem que la imatge es modifiqui

    //UNIFORM
    GLuint texUniform = glGetUniformLocation(shaderProgram, "u_texture");
    glUseProgram(shaderProgram);
    glUniform1i(texUniform, 0);
    
    //------------------------------------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, textureID); //Podem pintem la imatge
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        ///---------------------------------
        for (unsigned int i = 0; i < (sizeof(indices) / sizeof(indices[0])) / 3; i++) {
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * i * sizeof(GLuint)));
        }
        //glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
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
