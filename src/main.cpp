#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdio.h>

#include "shaders/load_shader.hpp"
#include "camera.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

GLFWwindow* win;
GLuint program;

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
        {1,1,1},
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

void glfwErrorCallback(int errorCode, const char* errorMessage) {
    printf("glfw error: %d %s\n", errorCode, errorMessage);
}

const float speed = 0.2;
const float speed_scale = 3;
void glfwCharCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    glm::vec3 move_speed = glm::vec3(speed,speed,speed) * glm::vec3((mods?speed_scale:1));

    switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window,true);
            break;
        case 87: // W
            camera->move(camera->direction * move_speed);
            break;
        case 83: // S
            camera->move(-(camera->direction * move_speed));
            break;
        case 65: // A
            camera->move(glm::cross(glm::vec3(0,1,0),camera->direction) * move_speed);
            break;
        case 68: // D
            camera->move(glm::cross(glm::vec3(0,1,0),-camera->direction) * move_speed);
            break;
        default:
            if (action == 0) {
                printf("\rKey pressed: %d mods: %d   ",key, mods);
                fflush(stdout);
            }
            break;
    }
}
void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {}
void glfwMousePosCallback(GLFWwindow* window, double x, double y) {}


void render() {

    glClearColor(1,0,0,1);
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
        printf("You fucking moron, you messed up the struct size, make it 16 byte aligned! struct size: %lld\n",sizeof(Block));
        return 1;
    }

#pragma region setup
    if (!glfwInit()) {
        printf("GLFW init failed!\n");
        return 1;
    }

    glfwSetErrorCallback(glfwErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    win = glfwCreateWindow(WIDTH, HEIGHT, "Voxel engine v2", NULL, NULL);
    if (!win) {
        printf("Window creation failed!\n");
        return 1;
    }

    glfwMakeContextCurrent(win);

    if (glewInit() != GLEW_OK) {
        printf("GLEW init failed!\n");
        return 1;
    }

    GLuint fragShader = loadShader("../src/shaders/frag_shader.glsl",GL_FRAGMENT_SHADER);
    GLuint vertexShader = loadShader("../src/shaders/vertex_shader.glsl",GL_VERTEX_SHADER);
    GLuint geometryShader = loadShader("../src/shaders/geometry_shader.glsl",GL_GEOMETRY_SHADER);

    program = glCreateProgram();

    glAttachShader(program,fragShader);
    glAttachShader(program,vertexShader);
    glAttachShader(program,geometryShader);
    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = new char[maxLength];
        glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);
        printf("Linking failed! Info log: %s\n",infoLog);

        delete[] infoLog;
        glDeleteShader(fragShader);
        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteProgram(program);

        exit(1);
    }

    glValidateProgram(program);

    GLint isValid = 0;
    glGetProgramiv(program, GL_VALIDATE_STATUS, (int *)&isValid);
    if (isValid == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = new char[maxLength];
        glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);
        printf("Linking failed! Info log: %s\n",infoLog);

        delete[] infoLog;
        glDeleteShader(fragShader);
        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteProgram(program);

        exit(1);
    }

    glDeleteShader(fragShader);
    glDeleteShader(vertexShader);
    glDeleteShader(geometryShader);

    glEnable(GL_DEPTH_TEST);
    glUseProgram(program);
#pragma endregion

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
    glfwGetFramebufferSize(win,&width,&height);
    glViewport(0,0,width,height);

    glfwSetKeyCallback(win,glfwCharCallback);
    glfwSetCursorPosCallback(win,glfwMousePosCallback);
    glfwSetMouseButtonCallback(win, glfwMouseButtonCallback);

    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();

        render();

        glfwSwapBuffers(win);
    }

    glfwDestroyWindow(win);
    glfwTerminate();
}

