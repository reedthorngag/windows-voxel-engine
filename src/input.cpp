#include <stdio.h>

#include "input.hpp"

Input::Input() {
    
}

void Input::press(unsigned int key) {
    keys[key] = true;
}

void Input::release(unsigned int key) {
    keys[key] = false;
}

void Input::onMouseMove(Player* player) {
   this->activePlayer = player;
}

void Input::glfwCharCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (action) {
        this->press(key);
    } else {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window,true);
                break;
            
            default:
                this->release(key);
                printf("\rKey pressed: %d scancode: %d mods: %d   ",key, scancode, mods);
                fflush(stdout);
                break;
        }
    }
}

void Input::glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {}

void Input::glfwMousePosCallback(GLFWwindow* window, double x, double y) {
    if (this->activePlayer)
        this->activePlayer->mouseMove(window,x,y);
}
