#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.hpp"
#include "generation/generator.hpp"

#ifndef _GLOBALS
#define _GLOBALS

const int CHUNK_SIZE = 512;
const int SUB_CHUNK_SIZE = 32;
const int CHUNK_SUB_CHUNKS = CHUNK_SIZE/SUB_CHUNK_SIZE;

const int WIDTH = 800;
const int HEIGHT = 600;

const double HALF_WIDTH = WIDTH/2.0;
const double HALF_HEIGHT = HEIGHT/2.0;

class Global {

    public:
        GLFWwindow* window;
        GLuint program;
        Input input;
        Game game;
        Generator generator;
};

const glm::vec3 startPos(0);

const float speed = 0.05;
const float speed_scale = 5;

enum block: short {
    AIR,
    GRASS,
    DIRT,
    STONE,
    _NULL = -1
};

struct Model {
    glm::vec3 color;
    unsigned int padding;
};

const Model _models[] = {
    Model{},
    Model{
        glm::vec3(0,1,0),
        0
    },
    Model{
        glm::vec3(0.5,0.35,0.35),
        0
    },
    Model{
        glm::vec3(0.2,0.2,0.2),
        0
    }
};

#endif



