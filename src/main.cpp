#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdio.h>

#include "shaders/load_shader.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "globals.hpp"
#include "setup.hpp"

#pragma pack(1)
struct Block {
    float color[3];
    unsigned int padding;
};

GLuint VAO;
GLuint VBO;

GLuint UBO;

alignas(16)
Block models[] = {
    Block{
        {1,0.1,0},
        0
    }
};

// float[n][0] => pos, first 10 bits is x, next 10 is y and last 12 is z
// float[n][1] => data, first 12 bits are block/model id, next 2 is the plane (0 = top, 1 = side, 2 = front)
//                  last bit is if its the positive or negative face of that plane
//                  remaining 17 bits are currently unused
float faces[][2] = {
    {
        (float)0,
        (float)0x6000
    }
};

Camera* camera;
Input input;

inline void glfwCharCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    input.glfwCharCallback(window,key,scancode,action,mods);
}

inline void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    input.glfwMouseButtonCallback(window,button,action,mods);
}

inline void glfwMousePosCallback(GLFWwindow* window, double x, double y) {
    input.glfwMousePosCallback(window,x,y);
}


void render() {

    glClearColor(0.001,0.001,0.05,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->updateUniforms();

    glUniformMatrix4fv(glGetUniformLocation(program, "chunkOffset"), 1, GL_FALSE, glm::value_ptr(glm::translate(glm::mat4(1.0),glm::vec3(0))));

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);

}

int main() {
    std::cout << "hello world!\n" << std::endl;

    if (sizeof(Block) != 16) {
        printf("You messed up the struct size, make it 16 byte aligned! struct size: %lld\n",sizeof(Block));
        return 1;
    }

    createWindow();
    setupOpenGl();

    glUseProgram(program);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);
    glVertexAttribPointer(0,1,GL_FLOAT, GL_FALSE, 2*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,1,GL_FLOAT, GL_FALSE, 2*sizeof(GL_FLOAT), (void*)sizeof(GL_FLOAT));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    glGenBuffers(1, &UBO);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(models), models, GL_STATIC_DRAW);

    glUniformBlockBinding(program,glGetUniformBlockIndex(program,"modelData"),0);

    camera = new Camera(program,glm::vec3(0,0,-3));

    int width,height;
    glfwGetFramebufferSize(window,&width,&height);
    glViewport(0,0,width,height);

    glfwSetKeyCallback(window,glfwCharCallback);
    glfwSetCursorPosCallback(window,glfwMousePosCallback);
    glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);

    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        render();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

