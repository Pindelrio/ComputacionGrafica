#include "Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;



std::string Shader::ReadTextFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open()) return "";
    
    std::stringstream stringbuffer;
    stringbuffer << file.rdbuf();
    file.close();
    return stringbuffer.str();
}

Shader::Shader()
{
    CreateAndCompileVertexShader(ReadTextFile("vertex.glsl").c_str());
    CreateAndCompileFragmentShader(ReadTextFile("fragment.glsl").c_str());
}

unsigned int Shader::CreateAndCompileVertexShader(const char* vertexShaderSource)
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    return vertexShader;
}

unsigned int Shader::CreateAndCompileFragmentShader(const char* fragmentShaderSource)
{
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    return fragmentShader;
}
