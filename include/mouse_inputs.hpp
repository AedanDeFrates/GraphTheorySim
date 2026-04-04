#ifndef MOUSE_INPUTS_HPP
#define MOUSE_INPUTS_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>  

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void mouse_button_callback(GLFWwindow*, int button, int action, int);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif