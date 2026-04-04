#include <glad/glad.h>   // Load OpenGL functions
#include <GLFW/glfw3.h>  // Windowing/input

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "graph.hpp"
#include "Shader.h"
#include "mouse_inputs.hpp"

//Shaders for Triangle
const char *triangleVertexShaderSource = "shaderSources/triangle.vs";
const char *triangleFragmentShaderSource = "shaderSources/triangle.fs";

//Shaders for Line
const char *lineVertexShaderSource = "shaderSources/line.vs";
const char *lineFragmentShaderSource = "shaderSources/line.fs";

//Screen
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//Camera
glm::vec3 camPos = glm::vec3(0.0f,0.0f,3.0f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f,-1.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0f / 2.0;
float fov = 45.0f;




void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {

    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {

    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {

    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {

    }
}

int main() 
{
    //===============================================================
    //                          INIT
    //===============================================================
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

    glViewport(0,0,SCR_WIDTH, SCR_HEIGHT);

    glEnable(GL_DEPTH_TEST);
    
    //=======================================================
    //========================================================
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    //=====================================================================
    //                        Configure Vertices
    //=====================================================================

    // Triangle Vertices
    float triangleVertices[] = {
        0.0f, 0.02f, 0.0f,
        -0.02f, -0.02f, 0.0f,
        0.02f, -0.02f, 0.0f
    };

    // Triangle Positions
    std::vector<glm::vec3> trianglePositions = graph_test().getTrianglePositions();

    // Lines
    std::vector<float> graphLineVertices = graph_test().getLineVectors();

    //=========================================================================
    //                        TRIANGLE VBO/VAO SETUP
    //=========================================================================
    unsigned int VBO, VAO;

    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    //=========================================================
    //                    LINE VBO/VAO SETUP
    //=========================================================

    unsigned int lineVBO, lineVAO;
    glGenBuffers(1, &lineVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);

    glGenVertexArrays(1, &lineVAO);
    glBindVertexArray(lineVAO);

    //glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, graphLineVertices.size() * sizeof(float), graphLineVertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //============================================================
    //                      SHADER SETUP
    //============================================================
    Shader triangleShader(triangleVertexShaderSource, triangleFragmentShaderSource );
    Shader lineShader(lineVertexShaderSource, lineFragmentShaderSource);


    //THREE SHADER OPERATIONS
    // 1): PROJECTION MATRIX
    // 2): VIEW MATRIX
    // 3): MODEL MATRIX
    

    //============================================================
    //                     CAMERA SETUP
    //============================================================




    //==============================================================
    //                      MAIN RENDER LOOP
    //==============================================================

    while(!glfwWindowShouldClose(window))
    {
        //Fram Time Logic
        float currFrameTime = static_cast<float>(glfwGetTime());
        deltaTime = currFrameTime - lastFrame;
        lastFrame = currFrameTime;


        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // 1): PROJECTION MATRIX
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH/ (float) SCR_HEIGHT, 0.1f, 100.0f);

        triangleShader.use();
        triangleShader.setMat4("projection", projection);
        
        // 2): VIEW MATRIX
        glm::mat4 view = glm::mat4(1.0f); //Set the view as identity matrix
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        triangleShader.setMat4("view", view);

        // render triangles
        glBindVertexArray(VAO);
        triangleShader.use();
        for(glm::vec3 pos : trianglePositions)
        {
            //3): MODEL MATRIX
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pos);

            triangleShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        lineShader.use();
        lineShader.setMat4("projection", projection);
        lineShader.setMat4("view", view);

        //render all lines from the line VBO
        glBindVertexArray(lineVAO);
        glm::mat4 model = glm::mat4(1.0f);
        lineShader.setMat4("model", model);
        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(graphLineVertices.size() / 3));


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}