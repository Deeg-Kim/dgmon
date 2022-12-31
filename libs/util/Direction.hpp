#ifndef DIRECTION_H
#define DIRECTION_H
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

namespace DGMon {
    enum class DirectionType {
        UP, DOWN, LEFT, RIGHT, NONE
    };
    
    const std::vector<DirectionType> ALL_DIRECTION_TYPES = {DirectionType::UP, DirectionType::DOWN, DirectionType::LEFT, DirectionType::RIGHT, DirectionType::NONE};

    class Direction {
        public:
            Direction(DirectionType directionType);
            DirectionType getAsEnum();
            sf::Vector2i getAsVector();
            const int getIdx();
        private:
            DirectionType enumRepresentation;
            sf::Vector2i vectorRepresentation;
            int indexRepresentation;
    };

    const Direction UP_DIRECTION (DirectionType::UP);
    const Direction DOWN_DIRECTION (DirectionType::DOWN);
    const Direction LEFT_DIRECTION (DirectionType::LEFT);
    const Direction RIGHT_DIRECTION (DirectionType::RIGHT);
    const Direction NONE_DIRECTION (DirectionType::NONE);
};


template<>
struct std::hash<DGMon::DirectionType> {
    std::size_t operator()(DGMon::DirectionType const& d) const noexcept
    {
        if (d == DGMon::DirectionType::UP) {
            return std::hash<int>{}(0);
        } else if (d == DGMon::DirectionType::DOWN) {
            return std::hash<int>{}(1);
        } else if (d == DGMon::DirectionType::LEFT) {
            return std::hash<int>{}(2);
        } else if (d == DGMon::DirectionType::RIGHT) {
            return std::hash<int>{}(3);    
        } else if (d == DGMon::DirectionType::NONE) {
            return std::hash<int>{}(4);
        } else {
            return std::hash<int>{}(-1);
        }
    }
};

#endif