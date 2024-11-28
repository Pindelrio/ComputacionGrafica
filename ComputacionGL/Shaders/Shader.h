#pragma once
#include <string>

class glad;
class GLFW;



class Shader
{
public:
    std::string ReadTextFile(const std::string& fileName);
    unsigned int vertexShader;
    unsigned int fragmentShader;

    Shader();
    unsigned int CreateAndCompileVertexShader(const char* vertexShaderSource);
    unsigned int CreateAndCompileFragmentShader(const char* fragmentShaderSource);
};
