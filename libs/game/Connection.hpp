#ifndef WARP_H
#define WARP_H

#include <string>
#include <utility>
#include "state/StateTransition.hpp"
#include "util/Util.hpp"

namespace DGMon {
    struct Connection {
        Connection(StateTransition transition, int x, int y, Direction direction)
        :transition(transition)
        ,x(x)
        ,y(y)
        ,direction(direction)
        {
            sf::Vector2i v1 (0, 0);
            sf::Vector2i v2 (0, 0);
            
            if (direction.getAsEnum() == DirectionType::UP) {
                v1 = sf::Vector2i(x * BLOCK_SIZE, y * BLOCK_SIZE + CONNECTION_TOLERANCE);
                v2 = sf::Vector2i((x + 1) * BLOCK_SIZE, y * BLOCK_SIZE + CONNECTION_TOLERANCE);
            } else if (direction.getAsEnum() == DirectionType::DOWN) {
                v1 = sf::Vector2i(x * BLOCK_SIZE, (y + 1) * BLOCK_SIZE - CONNECTION_TOLERANCE);
                v2 = sf::Vector2i((x + 1) * BLOCK_SIZE, (y + 1) * BLOCK_SIZE - CONNECTION_TOLERANCE);
            } else if (direction.getAsEnum() == DirectionType::LEFT) {
                v1 = sf::Vector2i(x * BLOCK_SIZE + CONNECTION_TOLERANCE, y * BLOCK_SIZE);
                v2 = sf::Vector2i(x * BLOCK_SIZE + CONNECTION_TOLERANCE, (y + 1) * BLOCK_SIZE);
            } else if (direction.getAsEnum() == DirectionType::RIGHT) {
                v1 = sf::Vector2i((x + 1) * BLOCK_SIZE - CONNECTION_TOLERANCE, y * BLOCK_SIZE);
                v2 = sf::Vector2i((x + 1) * BLOCK_SIZE - CONNECTION_TOLERANCE, (y + 1) * BLOCK_SIZE);
            }

            edge = std::make_pair(v1, v2);
        }
        
        int x;
        int y;
        std::pair<sf::Vector2i, sf::Vector2i> edge;
        Direction direction;
        StateTransition transition;
    };
};

#endif