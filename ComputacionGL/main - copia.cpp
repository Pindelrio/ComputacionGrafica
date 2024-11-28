#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <windows.h>

// float vertices[] = {
//     -0.5f,-0.5f,0.0f,
//      0.5f,-0.5f,0.0f,
//      0.0f, 0.5f,0.0f,
// };
int alternativeColorLocation;

// float vertices[] = {
//     -0.5f,-0.5f,0.0f,
//      0.5f,-0.5f,0.0f,
//      0.5f, 0.5f,0.0f,
//     
//     -0.5f,-0.5f,0.0f,
//     -0.5f, 0.5f,0.0f,
//      0.5f, 0.5f,0.0f
// };

float vertices[] = {
    0.0f,0.0f,0.0f,

    0.5f,0.0f,0.0f,
    0.0f,0.5f,0.0f,

    -0.5f,0.0f,0.0f,
    0.0f,0.5f,0.0f,

    -0.5f,0.0f,0.0f,
    0.0f,-0.5f,0.0f,

    0.5f,0.0f,0.0f,
    0.0f,-0.5f,0.0f,
     
};

// unsigned int indices[] = {
//
//     0,1,2,
//     4,0,2
//     
// };
unsigned int indices[] = {
    0,1,2,
    0,3,4,
    0,5,6,
    0,7,8
};
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 alternativeColor;\n"
"void main()\n"
"{\n"
"   FragColor = alternativeColor;\n"
"}\n\0";

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

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


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

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   
    
    int i = 0;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.9f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        //glfwGetTime();
        
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        // glUniform4f(alternativeColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
        // glDrawElements(GL_TRIANGLES, std::size(indices)/2, GL_UNSIGNED_INT, 0);
        //
        // glUniform4f(alternativeColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
        // glDrawElements(GL_TRIANGLES, std::size(indices)/2, GL_UNSIGNED_INT, (int*)NULL +3);

        int j=0;
        while (j<=3)
        {
            Draw(i, j);
            j++;
        }
        i=i+4;
        if (i>=16)
            i=0;
        Sleep(500);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
    //glViewport(0, 0, 800, 600);

    glfwTerminate();

    return 0;
}
