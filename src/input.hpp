#include <GLFW/glfw3.h>

#include "player.hpp"

#ifndef _INPUT
#define _INPUT

class Input {
    private:
        Player* activePlayer;
    public:
        bool keys[512] = { 0 };

        Input();

        void press(unsigned int key);
        void release(unsigned int key);

        void onMouseMove(Player* player);

        void glfwCharCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        void glfwMousePosCallback(GLFWwindow* window, double x, double y);
};

#endif
