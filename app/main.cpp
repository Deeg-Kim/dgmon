#include "game/Game.hpp"
#include "util/Util.hpp"
#include "data/LayoutLoader.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace DGMon;

int main() {
    auto window = sf::RenderWindow{ { 1280u, 960u }, "DG Mon"};
    window.setFramerateLimit(24);
    window.setVerticalSyncEnabled (true);
    window.setKeyRepeatEnabled(false);

    LayoutLoader layoutLoader;

    Trainer trainer(1280 / 2, 960 / 2);
    trainer.refresh();

    auto zones = layoutLoader.getZone("pallet_town");

    // Flags for key pressed
    bool moving = false;
    Direction dir = NONE_DIRECTION;

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
                        dir = UP_DIRECTION;
                        break;
                    case sf::Keyboard::S: 
                        moving = true;
                        dir = DOWN_DIRECTION;
                        break;
                    case sf::Keyboard::A: 
                        moving = true;
                        dir = LEFT_DIRECTION;
                        break;
                    case sf::Keyboard::D: 
                        moving = true;
                        dir = RIGHT_DIRECTION;
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
        window.draw(zones.first);
        window.draw(trainer);
        window.draw(zones.second);
        window.display();
    }

    return 0;
}