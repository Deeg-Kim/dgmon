#include "Direction.hpp"
#include "SFML/System/Vector2.hpp"
#include <stdexcept>

using namespace DGMon;

Direction::Direction(DirectionType type)
:enumRepresentation(type)
{
    if (type == DirectionType::UP) {
        vectorRepresentation = sf::Vector2i(0, -1);
        indexRepresentation = 0;
    } else if (type == DirectionType::DOWN) {
        vectorRepresentation = sf::Vector2i(0, 1);
        indexRepresentation = 1;
    } else if (type == DirectionType::LEFT) {
        vectorRepresentation = sf::Vector2i(-1, 0);
        indexRepresentation = 2;
    } else if (type == DirectionType::RIGHT) {
        vectorRepresentation = sf::Vector2i(1, 0);
        indexRepresentation = 3;
    } else if (type == DirectionType::NONE) {
        vectorRepresentation = sf::Vector2i(0, 0);
        indexRepresentation = 4;
    } else {
        throw std::invalid_argument("Unknown direction type.");
    }
}

DirectionType Direction::getAsEnum() 
{
    return enumRepresentation;
}

sf::Vector2i Direction::getAsVector() 
{
    return vectorRepresentation;
}

const int Direction::getIdx() 
{
    return indexRepresentation;
}