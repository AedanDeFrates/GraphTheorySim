#include "mouse_inputs.hpp"

void mouse_button_callback(GLFWwindow*, int button, int action, int)
{
    //RIGHT & LEFT CLICK DOWN
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        std::cout << "right click\n";
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        std::cout << "left click\n";
    }

    //RIGHT & LEFT CLICK UP
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        std::cout << "left click release\n";
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        std::cout << "right click release\n";
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << "x = " << xpos << "\n" << "y = " << ypos << "\n";
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << "x = " << xoffset << "\n" << "y = " << yoffset << "\n";
}