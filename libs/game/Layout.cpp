#include "Layout.hpp"
#include "SFML/System/Vector2.hpp"
#include <stdexcept>
#include <utility>

using namespace DGMon;

Layout::Layout(Zone layer0, Zone layer1) 
:layer0(layer0)
,layer1(layer1)
,trainer(Trainer (1280 / 2, 704 / 2))
{
    trainer.refresh();
}

Layout::~Layout()
{
}

void Layout::draw(sf::RenderWindow* window) {
    window->draw(layer0);
    window->draw(trainer);
    window->draw(layer1);
}

void Layout::movePrimaryPlayer(Direction dir) {
    int collisionHeight = layer1.getMaxHeight(getTrainerEdge(dir), dir);
    if (trainer.getHeight() >= collisionHeight) {
        trainer.move(dir);
    }
}

std::pair<sf::Vector2i, sf::Vector2i> Layout::getTrainerEdge(Direction dir) {
    auto boundary = trainer.getBoundary();
    switch (dir.getAsEnum()) {
        case UP:
            return std::make_pair(sf::Vector2i (boundary.first.x, boundary.first.y),sf::Vector2i (boundary.second.x, boundary.first.y));
        case DOWN:
            return std::make_pair(sf::Vector2i (boundary.first.x, boundary.second.y),sf::Vector2i (boundary.second.x, boundary.second.y));
        case LEFT:
            return std::make_pair(sf::Vector2i (boundary.first.x, boundary.first.y), sf::Vector2i (boundary.first.x, boundary.second.y));
        case RIGHT:
            return std::make_pair(sf::Vector2i (boundary.second.x, boundary.first.y), sf::Vector2i (boundary.second.x, boundary.second.y));
        default:
            throw new std::invalid_argument("Unknown direction.");
    }
}