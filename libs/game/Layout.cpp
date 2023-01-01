#include "Layout.hpp"
#include "SFML/System/Vector2.hpp"
#include "game/Connection.hpp"
#include "state/State.hpp"
#include "state/StateTransition.hpp"
#include "util/Const.hpp"
#include "util/Direction.hpp"
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
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
,view(
    sf::Vector2f(static_cast<double>(widthBlocks) * BLOCK_SIZE / 2, static_cast<double>(heightBlocks) * BLOCK_SIZE / 2), sf::Vector2f(800.f, 600.f)
    )
,backgroundLayers(backgroundLayers)
,foregroundLayers(foregroundLayers)
,trainer(std::make_shared<Trainer>(static_cast<double>(widthBlocks) * BLOCK_SIZE / 2, static_cast<double>(heightBlocks) * BLOCK_SIZE / 2))
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


    state.id = id;
    state.type = StateType::LAYOUT;

    for (auto c : connections) {
        connectionsByDirection.at(c->direction.getAsEnum()).push_back(c);
        connectionsByName.insert({c->transition.toAttribute, c});
    }

    std::cout << connectionsByName.size() << std::endl;
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

void Layout::handlePreviousTransition(StateTransition transition) {
    // came from another layout
    if (transition.type == StateTransitionType::CONNECT) {
        // TODO: do check here if there isn't a return connection
        auto c = connectionsByName.at(transition.fromAttribute);

        int x, y;

        if (c->direction.getAsEnum() == DirectionType::UP) {
            x = c->x * BLOCK_SIZE + TILE_MAP_TILE_SIZE;
            y = TILE_MAP_TILE_SIZE;
        } else if (c->direction.getAsEnum() == DirectionType::DOWN) {
            x = c->x * BLOCK_SIZE + TILE_MAP_TILE_SIZE;
            y = (heightBlocks - 1) * BLOCK_SIZE + TILE_MAP_TILE_SIZE;
        } else if (c->direction.getAsEnum() == DirectionType::LEFT) {
            x = TILE_MAP_TILE_SIZE;
            y = c->y * BLOCK_SIZE + TILE_MAP_TILE_SIZE;
        } else if (c->direction.getAsEnum() == DirectionType::RIGHT) {
            x = (widthBlocks - 1) * BLOCK_SIZE + TILE_MAP_TILE_SIZE;
            y = c->y * BLOCK_SIZE + TILE_MAP_TILE_SIZE;
        }
        trainer->setLocation(x, y);
        view.setCenter(sf::Vector2f (x, y));
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
                if (edge.first.y <= cEdge.first.y && 
                    edge.first.x >= cEdge.first.x &&
                    edge.second.x <= cEdge.second.x) {
                    transition = c->transition;
                }
            }
        } else if (dirEnum == DirectionType::DOWN) {
            view.move(0, trainer->spriteSpeed);

            for (auto c : connectionsByDirection.at(DirectionType::DOWN)) {
                auto cEdge = c->edge;
                if (edge.first.y >= cEdge.first.y && 
                    edge.first.x >= cEdge.first.x &&
                    edge.second.x <= cEdge.second.x) {
                    transition = c->transition;
                }
            }
        } else if (dirEnum == DirectionType::LEFT) {
            view.move(-trainer->spriteSpeed, 0);

            for (auto c : connectionsByDirection.at(DirectionType::LEFT)) {
                auto cEdge = c->edge;
                if (edge.first.x <= cEdge.first.x && 
                    edge.first.y >= cEdge.first.y &&
                    edge.second.y <= cEdge.second.y) {
                    transition = c->transition;
                }
            }
        } else if (dirEnum == DirectionType::RIGHT) {
            view.move(trainer->spriteSpeed, 0);

            for (auto c : connectionsByDirection.at(DirectionType::RIGHT)) {
                auto cEdge = c->edge;
                if (edge.first.x >= cEdge.first.x && 
                    edge.first.y >= cEdge.first.y &&
                    edge.second.y <= cEdge.second.y) {
                    transition = c->transition;
                }
            }
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