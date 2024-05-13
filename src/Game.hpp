#include <glm/glm.hpp>

#include "Input.hpp"
#include "Player.hpp"

class Game {

    public:
        Input input;
        Player* player = new Player(glm::vec3(0));

        Game();
        ~Game();

        void start();
};

