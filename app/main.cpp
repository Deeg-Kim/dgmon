#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "game/Game.hpp"
#include "util/Util.hpp"
#include "data/LayoutLoader.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace DGMon;

int main() {
    auto window = sf::RenderWindow{ { 600u,  450u }, "DG Mon"};
    window.setFramerateLimit(24);
    window.setVerticalSyncEnabled (true);
    window.setKeyRepeatEnabled(false);

    LayoutLoader layoutLoader;

    auto layout = layoutLoader.getLayout("pallet_town");

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
            layout->handleWASDMovement(dir);
        }

        window.clear();
        layout->draw(&window);
        window.display();
    }

    return 0;
}