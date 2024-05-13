#include <GLFW/glfw3.h>

#ifndef _INPUT
#define _INPUT

class Input {
    private:
        void (*mouseCallback)(GLFWwindow* win, double x, double y);
    public:
        bool keys[255] = { 0 };

        Input();

        void press(unsigned int key);
        void release(unsigned int key);

        void onMouseMove(void callback(GLFWwindow* win, double x, double y));
        void defaultCallback(void* args...);

        void glfwCharCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        void Input::glfwMousePosCallback(GLFWwindow* window, double x, double y);
};

#endif
