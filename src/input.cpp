#include <stdio.h>

#include "input.hpp"

Input::Input() {
    this->mouseCallback;
}

void Input::press(unsigned int key) {
    keys[key] = true;
}

void Input::release(unsigned int key) {
    keys[key] = false;
}

void Input::onMouseMove(void callback(GLFWwindow* win, double x, double y)) {
    this->mouseCallback = callback;
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
    this->mouseCallback(window, x, y);
}
