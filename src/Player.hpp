#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "Camera.hpp"

#ifndef _Player
#define _Player

class Player {

    public:
        Camera* camera;
        glm::vec3 pos;
        float height = 1.69;

        Player(glm::vec3 startPos);
        ~Player();

        void move(unsigned int ms);
        void mouseMove(GLFWwindow* win, double x, double y);
};

#endif