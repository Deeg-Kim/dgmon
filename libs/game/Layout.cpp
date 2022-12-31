#include "Layout.hpp"
#include "SFML/System/Vector2.hpp"
#include "game/Connection.hpp"
#include "state/StateTransition.hpp"
#include "util/Const.hpp"
#include "util/Direction.hpp"
#include <memory>
#include <optional>
#include <utility>

using namespace DGMon;

Layout::Layout(
    std::string id,
    int widthBlocks,
    int heightBlocks,
    std::vector<std::shared_ptr<ZoneLayer>> backgroundLayers, 
    std::vector<std::shared_ptr<ZoneLayer>> foregroundLayers,
    std::vector<std::shared_ptr<Connection>> connections
) 
:id(id)
,widthBlocks(widthBlocks)
,heightBlocks(heightBlocks)
,view(sf::Vector2f(640.f, 480.f), sf::Vector2f(800.f, 600.f))
,backgroundLayers(backgroundLayers)
,foregroundLayers(foregroundLayers)
,trainer(std::make_shared<Trainer>(1280 / 2, 960 / 2))
{
    trainer->load();
    for (auto layer : backgroundLayers) {
        layer->load();
    }

    for (auto layer : foregroundLayers) {
        layer->load();
    }

    for (auto type : ALL_DIRECTION_TYPES) {
        connectionsByDirection.insert({type, std::vector<std::shared_ptr<Connection>> {}});
    }

    for (auto c : connections) {
        connectionsByDirection.at(c->direction.getAsEnum()).push_back(c);
    }
}

Layout::~Layout()
{
    for (auto layer : backgroundLayers) {
        layer->~ZoneLayer();
    }

    for (auto layer : foregroundLayers) {
        layer->~ZoneLayer();
    }
}

void Layout::draw(sf::RenderWindow* window) {
    window->setView(view);
    for (auto layer : backgroundLayers) {
        window->draw(*layer);
    }
    window->draw(*trainer);
    for (auto layer : foregroundLayers) {
        window->draw(*layer);
    }
}

std::optional<StateTransition> Layout::handleWASDMovement(Direction dir) 
{
    int collisionHeight = 0;

    auto edge = getTrainerEdge(dir);

    // check collisions
    for (auto layer : backgroundLayers) {
        collisionHeight = std::max(collisionHeight, layer->getMaxHeight(edge, dir));
    }
    for (auto layer : foregroundLayers) {
        collisionHeight = std::max(collisionHeight, layer->getMaxHeight(edge, dir));
    }

    std::optional<StateTransition> transition = std::nullopt;

    if (trainer->getHeight() >= collisionHeight) {
        auto dirEnum = dir.getAsEnum();
        trainer->move(dir);

        if (dirEnum == DirectionType::UP) {
            view.move(0, -trainer->spriteSpeed);

            for (auto c : connectionsByDirection.at(DirectionType::UP)) {
                auto cEdge = c->edge;
                if (trainer->getPosition().y <= cEdge.first.y && 
                    trainer->getPosition().x >= cEdge.first.x &&
                    trainer->getPosition().x <= cEdge.second.x) {
                    transition = c->transition;
                }
            }
        } else if (dirEnum == DirectionType::DOWN) {
            view.move(0, trainer->spriteSpeed);
        } else if (dirEnum == DirectionType::LEFT) {
            view.move(-trainer->spriteSpeed, 0);
        } else if (dirEnum == DirectionType::RIGHT) {
            view.move(trainer->spriteSpeed, 0);
        }
    }

    return transition;
}

std::pair<sf::Vector2i, sf::Vector2i> Layout::getTrainerEdge(Direction dir) {
    auto boundary = trainer->getBoundary();
    switch (dir.getAsEnum()) {
        case DirectionType::UP:
            return std::make_pair(sf::Vector2i (boundary.first.x, boundary.first.y),sf::Vector2i (boundary.second.x, boundary.first.y));
        case DirectionType::DOWN:
            return std::make_pair(sf::Vector2i (boundary.first.x, boundary.second.y),sf::Vector2i (boundary.second.x, boundary.second.y));
        case DirectionType::LEFT:
            return std::make_pair(sf::Vector2i (boundary.first.x, boundary.first.y), sf::Vector2i (boundary.first.x, boundary.second.y));
        case DirectionType::RIGHT:
            return std::make_pair(sf::Vector2i (boundary.second.x, boundary.first.y), sf::Vector2i (boundary.second.x, boundary.second.y));
        default:
            throw new std::invalid_argument("Unknown direction.");
    }
}

State Layout::getState()
{
    return state;
}