#include <glm/glm.hpp>

#include "Input.hpp"
#include "Player.hpp"

#ifndef _Game
#define _Game

class Game {

    public:
        Input input;
        Player* player = new Player(glm::vec3(0));

        Game();
        ~Game();

        void start();
};

Game game;

#endif
