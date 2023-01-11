#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


//#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

struct VertexStream
{
    float Positions[2];
};

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

    VertexStream Verts[8] = {
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

    //Vertex Buffer 
    VertexBuffer VB(Verts, 8 * sizeof(VertexStream));

    //BufferLayout
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);


    //IndexBuffers
    IndexBuffer First_Shape(indices1, 6);
    IndexBuffer Second_Shape(indices2, 6);
    


    //Shaders
    Shader VertexShader (GL_VERTEX_SHADER,"res/shaders/VertexShader.shader");
    Shader FragmentShader (GL_FRAGMENT_SHADER,"res/shaders/FragmentShader.shader");
    
    VertexShader.Bind();
    FragmentShader.Bind();
    
    int Uniformlocation = FragmentShader.GetUniformLocation("u_Color");
    
    
    float red = 0.0f,increment = 0.0001f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        if (Uniformlocation != -1)
            FragmentShader.SetUnifor4F(Uniformlocation, red, 0.0f, 1.0f, 1.0f);

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
            //VertexStream[i] += 0.0001f;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

}
