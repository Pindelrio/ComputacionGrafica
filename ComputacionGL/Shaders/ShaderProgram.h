#pragma once

class glad;

class ShaderProgram
{
public:
    unsigned int shaderProgram;
    ShaderProgram();
    unsigned int CreateAttachAndLinkShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
};
