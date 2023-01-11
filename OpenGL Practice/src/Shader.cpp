#include "Shader.h"


int Shader::GetUniformLocation(const std::string& name)const
{
    return glGetUniformLocation(ProgramID, "u_Color");
}

Shader::Shader(unsigned int type,const std::string& filePath):FilePath(filePath),Type(type),ShaderID(0)
{
    Compile(Parse());
    Create();
}
Shader::~Shader()
{
    glDeleteShader(ShaderID);
    glDeleteProgram(ProgramID);
}
void Shader::Bind()const
{
    glUseProgram(ProgramID);
}
void Shader::Unbind()const
{
    glUseProgram(0);
    glDeleteShader(ShaderID);
}
void Shader::SetUnifor4F(int location, float f1, float f2, float f3, float f4)
{
    if (location != -1)
            glUniform4f(location, f1,f2,f3,f4);
}
void Shader::Create()
{
    ProgramID = glCreateProgram();
    //if no ID generated  crash
    glAttachShader(ProgramID, ShaderID);

    glLinkProgram(ProgramID);
    glValidateProgram(ProgramID);
}
std::string Shader::Parse()
{
    std::string line;
    std::stringstream shaderstream;
    std::ifstream stream(FilePath);
    while (getline(stream, line))
    {
        shaderstream << line << "\n";
    }
    return shaderstream.str();
}

void Shader::Compile(const std::string& source)
{
    ShaderID = glCreateShader(Type);
    //if no ID generated  crash
    const char* src = source.c_str();
    glShaderSource(ShaderID, 1, &src, nullptr);
    glCompileShader(ShaderID);
}