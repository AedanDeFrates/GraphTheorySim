#include "inputs.hpp"
#include "graph.hpp"
#include "camera.hpp"

glm::vec3 initDragPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 currPos = glm::vec3(0.0f, 0.0f, 0.0f);

bool rightClickPress = false;
bool leftClickPress = false;

bool leftControlPress = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int modes)
{
    if(key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
    {
        leftControlPress = true;
    }
    if(key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE)
    {
        leftControlPress = false;
    }
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //RIGHT & LEFT CLICK DOWN
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        rightClickPress = true;

        double x, y;
        glfwGetCursorPos(window, &x, &y);
        initDragPos = glm::vec3(x, y, 0.0f);
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        leftClickPress = true;
        if(leftControlPress)
        {
            std::cout << "CREATE NEW VERTEX";
        }
    }

    //RIGHT & LEFT CLICK UP
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        rightClickPress = false;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        leftClickPress = false;
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    currPos.x = xpos; currPos.y = ypos;

    if (rightClickPress)
    {
        glm::vec3 deltaVector = currPos - initDragPos;

        float sensitivity = 0.01f;

        camera.Position += -camera.Right * deltaVector.x * sensitivity;
        camera.Position +=  camera.Up    * deltaVector.y * sensitivity;

        initDragPos = currPos;
    }
    std::cout << "x = " << xpos << " | y = " << ypos << "\n";
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    float zoomSpeed = 0.01f;
    camera.fov -= (float)yoffset;
    if (camera.fov < 1.0f) camera.fov = 1.0f;
    if (camera.fov > 45.0f) camera.fov = 45.0f;
}

