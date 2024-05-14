
#include "globals.hpp"
#include "Player.hpp"

extern GLuint program;
extern Game game;

Player::Player(glm::vec3 startPos) {
    this->pos = startPos;
    this->camera = new Camera(program, glm::vec3(0,this->height,0));
}

Player::~Player() {
    delete this->camera;
}

void Player::move(unsigned int ms) {
    glm::vec3 move_speed = glm::vec3(speed,speed,speed) * glm::vec3((mods?speed_scale:1) * ms);
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
}

void Player::mouseMove(GLFWwindow* win, double x, double y) {

}
