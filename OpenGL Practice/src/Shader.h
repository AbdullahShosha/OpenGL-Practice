#pragma once
#include <string>
#include<sstream>
#include <fstream>
#include<GL/glew.h>
class Shader
{
private:
	unsigned int ShaderID;
	unsigned int ProgramID;
	std::string FilePath;
	unsigned int Type;


	
	void Compile(const std::string& source);
	std::string Parse();
	void Create();
public :
	Shader(unsigned int type,const std::string& filePath);
	~Shader();
	void Bind()const;
	void Unbind()const;
	void SetUnifor4F(int location,float f1,float f2,float f3,float f4);
	int GetUniformLocation(const std::string& name)const;
};