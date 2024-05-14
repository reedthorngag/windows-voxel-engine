
#include "globals.hpp"
#include "Player.hpp"

extern Global global;

Player::Player(glm::vec3 startPos) {
    this->pos = startPos;
    this->camera = new Camera(global.program, glm::vec3(0,this->height,0));
}

Player::~Player() {
    delete this->camera;
}

void Player::move(unsigned int ms) {
    glm::vec3 move_speed = glm::vec3(speed,speed,speed) * glm::vec3((speed_scale) * ms);
    if (global.input.keys[87])
        camera->move(camera->direction * move_speed);
    if (global.input.keys[83])
        camera->move(-(camera->direction * move_speed));
    if (global.input.keys[65])
        camera->move(glm::cross(glm::vec3(0,1,0),camera->direction) * move_speed);
    if (global.input.keys[68])
        camera->move(glm::cross(glm::vec3(0,1,0),-camera->direction) * move_speed);
}

void Player::mouseMove(GLFWwindow* win, double x, double y) {
    
}
