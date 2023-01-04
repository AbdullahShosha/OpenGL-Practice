#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<fstream>
#include <string>
#include <sstream>

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
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();
    float Positions[12] =
    {
        -0.2f ,-0.2f,
        -0.2f , 0.2f,
         0.2f , 0.2f,

        -0.2f , -0.2f,
         0.2f ,  0.2f,
         0.2f , -0.2f
    };
    unsigned int BufferID;
    glGenBuffers(1, &BufferID);
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), Positions, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::string VertexShaderString = ParseShader("res/shaders/VertexShader.shader");
    std::string FragmentFhaderString = ParseShader("res/shaders/FragmentShader.shader");
    
    unsigned int Vshader = CreateShader(GL_VERTEX_SHADER, VertexShaderString);
    unsigned int Fshader = CreateShader(GL_FRAGMENT_SHADER, FragmentFhaderString);
    
    glUseProgram(Vshader);
    glUseProgram(Fshader);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        //for (int i = 0; i < 12; i++)
            //Positions[i] += 0.0001f;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

}
