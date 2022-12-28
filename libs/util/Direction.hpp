#ifndef DIRECTION_H
#define DIRECTION_H
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

namespace DGMon {
    enum DirectionType {
        UP, DOWN, LEFT, RIGHT, NONE
    };
    
    class Direction {
        public:
            Direction(DirectionType directionType);
            DirectionType getAsEnum();
            sf::Vector2i getAsVector();
        private:
            DirectionType enumRepresentation;
            sf::Vector2i vectorRepresentation;
    };

    const Direction UP_DIRECTION (UP);
    const Direction DOWN_DIRECTION (DOWN);
    const Direction LEFT_DIRECTION (LEFT);
    const Direction RIGHT_DIRECTION (RIGHT);
    const Direction NONE_DIRECTION (NONE);
};

#endif