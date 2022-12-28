#include "game/Game.hpp"
#include "util/Util.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main() {
    auto window = sf::RenderWindow{ { 1440u, 810u }, "DG's Maze Project" };
    window.setFramerateLimit(24);
    window.setVerticalSyncEnabled (true);
    window.setKeyRepeatEnabled(false);

    DGMon::Trainer trainer(1440 / 2, 810 / 2);
    trainer.refresh();

    // Flags for key pressed
    bool moving = false;
    DGMon::Direction dir = DGMon::NONE_DIRECTION;

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // If a key is pressed
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::W: 
                        moving = true;
                        dir = DGMon::UP_DIRECTION;
                        break;
                    case sf::Keyboard::S: 
                        moving = true;
                        dir = DGMon::DOWN_DIRECTION;
                        break;
                    case sf::Keyboard::A: 
                        moving = true;
                        dir = DGMon::LEFT_DIRECTION;
                        break;
                    case sf::Keyboard::D: 
                        moving = true;
                        dir = DGMon::RIGHT_DIRECTION;
                        break;
                    default : break;
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::W: case sf::Keyboard::S: case sf::Keyboard::A: case sf::Keyboard::D: 
                        moving = false; 
                        break;
                    default : break;
                }
            }
        }

        if (moving) {
            trainer.move(dir);
        }

        window.clear();
        window.draw(trainer);
        window.display();
    }

    return 0;
}