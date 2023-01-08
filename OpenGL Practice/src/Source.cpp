#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<fstream>
#include <string>
#include <sstream>


//#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

static std::string ParseShader(const std::string& filepath)
{
    std::string line;
    std::stringstream shaderstream;
    std::ifstream stream(filepath);
    while (getline(stream, line))
    {
        shaderstream << line << "\n";
    }
    return shaderstream.str();
}

static unsigned int compileshader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    return id;
}

static int CreateShader(unsigned int type,const std::string& ShaderString)
{
    unsigned int program = glCreateProgram();
    unsigned int ReadyShader = compileshader(type, ShaderString);

    glAttachShader(program, ReadyShader);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(ReadyShader);

    return program;
}



int main()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    GLFWwindow* window;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();
    float Positions[16] =
    {
        -1.0f ,  -1.0f,//0
        -0.6f ,  -1.0f,//1
        -0.6f ,  -0.6f,//2
        -1.0f ,  -0.6f,//3

         0.6f ,  0.6f, //4
         1.0f ,  0.6f, //5
         1.0f ,  1.0f, //6
         0.6f ,  1.0f  //7
    };
    unsigned int indices1[6] =
    { 0,1,2  ,3,0,1  };
    unsigned int indices2[6] = 
    { 4,5,6  ,4,6,7  };

    //first square 
    VertexBuffer VB(Positions, 16 * sizeof(float));

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    IndexBuffer First_Shape(indices1, 6);
    
    IndexBuffer Second_Shape(indices2, 6);
    

    std::string VertexShaderString = ParseShader("res/shaders/VertexShader.shader");
    std::string FragmentFhaderString = ParseShader("res/shaders/FragmentShader.shader");
    
    unsigned int Vshader = CreateShader(GL_VERTEX_SHADER, VertexShaderString);
    unsigned int Fshader = CreateShader(GL_FRAGMENT_SHADER, FragmentFhaderString);
    
    glUseProgram(Vshader);
    glUseProgram(Fshader);

    int location = glGetUniformLocation(Fshader,"u_Color");
    float red = 0.0f,increment = 0.0001f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        if (location != -1)
            glUniform4f(location, red, 0.0f, 1.0f, 1.0f);

        First_Shape.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,nullptr);
        
        Second_Shape.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,nullptr);


        if (red >= 1.0f)
            increment = -0.0001f;
        else if (red <= 0.0)
            increment = 0.0001f;
        red += increment;
        //for (int i = 0; i < 12; i++)
            //Positions[i] += 0.0001f;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

}
