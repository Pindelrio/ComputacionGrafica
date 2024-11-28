#include "ShaderProgram.h"
#include <glad/glad.h>

ShaderProgram::ShaderProgram()
{
}

unsigned int ShaderProgram::CreateAttachAndLinkShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    return shaderProgram;
}
