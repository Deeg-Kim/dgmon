#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "SFML/System/Vector2.hpp"
#include <utility>
#include <SFML/Graphics.hpp>

namespace DGMon {
    class Collidable {
        virtual int getHeight() { return 0; };
        virtual std::pair<sf::Vector2i, sf::Vector2i> getBoundary() { return std::make_pair(sf::Vector2i(0, 0), sf::Vector2i(0, 0)); };
    };
};

#endif