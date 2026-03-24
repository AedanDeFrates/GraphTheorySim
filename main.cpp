#include <glad/glad.h>   // Load OpenGL functions
#include <GLFW/glfw3.h>  // Windowing/input

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "graph.hpp"

//Shaders for Triangle
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

//Shaders for Line
const char *lineVertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";
const char *lineFragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor; \n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0,1.0,1.0,1.0);\n"
    "}\0";


// Callback for window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to creat GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" <<std::endl;
        return -1;
    }

    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

    //=====================================================================
    //                        Configure Vertices
    //=====================================================================

    // Triangle Vertices
    float triangleVertices[] = {
        0.0f, 0.2f, 0.0f,
        -0.2f, -0.2f, 0.0f,
        0.2f, -0.2f, 0.0f
    };

    // Triangle Positions
    std::vector<glm::vec3> trianglePositions = test_graph().getTrianglePositions();

    // Line Vertices
    float lineVertices[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };
    // Line Positions
    // Head
    std::vector<glm::vec3> lineStartPos = test_graph().getEdgeTailVectors();
    std::vector<glm::vec3> lineEndPos = test_graph().getEdgeHeadVectors();

    //funct.for.line.positions

    // Lines
    std::vector<float> graphLineVertices = test_graph().mkLineVectors();

    //=======================================================================
    //                        TRIANGLE SHADER SETUP
    //=======================================================================
    //create and compile vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    //create and compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //create shader program object
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //=========================================================================
    //                        TRIANGLE VBO/VAO SETUP
    //=========================================================================
    unsigned int VBO, VAO;

    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    //change sizeof(vertices) <--> triangleVertices.size() * sizeof(float)
    //change vertices <--> triangleVertices.data()
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    //========================================================
    //========================================================

    unsigned int lineVertexShader, lineFragmentShader;

    lineVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(lineVertexShader, 1, &lineVertexShaderSource, NULL);
    glCompileShader(lineVertexShader);

    lineFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(lineFragmentShader, 1, &lineFragmentShaderSource, NULL);
    glCompileShader(lineFragmentShader);

    unsigned int lineShaderProgram;
    lineShaderProgram = glCreateProgram();

    glAttachShader(lineShaderProgram, lineVertexShader);
    glAttachShader(lineShaderProgram, lineFragmentShader);
    glLinkProgram(lineShaderProgram);

    glDeleteShader(lineVertexShader);
    glDeleteShader(lineFragmentShader);

    //=========================================================
    //=========================================================

    unsigned int lineVBO, lineVAO;
    glGenBuffers(1, &lineVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);

    glGenVertexArrays(1, &lineVAO);
    glBindVertexArray(lineVAO);

    //glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, graphLineVertices.size() * sizeof(float), graphLineVertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glUseProgram(lineShaderProgram);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // activate triangle shader
        glUseProgram(shaderProgram);
        
        // render triangles
        glBindVertexArray(VAO);

        for(glm::vec3 pos : trianglePositions)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pos);

            //MUST IMPL SHADER CLASS FOR TRIANGLE

            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        glUseProgram(lineShaderProgram);
        glBindVertexArray(lineVAO);

        for(unsigned int i = 0; i < lineEndPos.size(); i++)
        {
            glm::mat4 endModel = glm::mat4(1.0f);
            endModel = glm::translate(endModel, lineEndPos.at(i));
            

            glDrawArrays(GL_LINES, 0, 2);
        }

        glDrawArrays(GL_LINES, 0, graphLineVertices.size()/2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}