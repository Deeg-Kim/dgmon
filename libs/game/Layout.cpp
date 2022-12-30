#include "Layout.hpp"

using namespace DGMon;

Layout::Layout(std::shared_ptr<Zone> layer0, std::shared_ptr<Zone> layer1, std::shared_ptr<Zone> layer2) 
:layer0(layer0)
,layer1(layer1)
,layer2(layer2)
,trainer(std::make_shared<Trainer>(1280 / 2, 704 / 2))
{
    trainer->refresh();
    layer0->load();
    layer1->load();
    layer2->load();
}

Layout::~Layout()
{
    layer0->~Zone();
    layer1->~Zone();
    layer2->~Zone();
}

void Layout::draw(sf::RenderWindow* window) {
    window->draw(*layer0);
    window->draw(*layer1);
    window->draw(*trainer);
    window->draw(*layer2);
}

void Layout::movePrimaryPlayer(Direction dir) {
    int collisionHeight = std::max(layer1->getMaxHeight(getTrainerEdge(dir), dir), layer2->getMaxHeight(getTrainerEdge(dir), dir));
    if (trainer->getHeight() >= collisionHeight) {
        trainer->move(dir);
    }
}

std::pair<sf::Vector2i, sf::Vector2i> Layout::getTrainerEdge(Direction dir) {
    auto boundary = trainer->getBoundary();
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