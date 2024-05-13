#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef _GLOBALS
#define _GLOBALS

const int WIDTH = 800;
const int HEIGHT = 600;

const double HALF_WIDTH = WIDTH/2.0;
const double HALF_HEIGHT = HEIGHT/2.0;

GLFWwindow* window;
GLuint program;

glm::vec3 startPos(0);

const float speed = 0.05;
const float speed_scale = 5;

#endif



