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
    std::shared_ptr<Trainer> trainer,
    std::vector<std::shared_ptr<ScreenLayer>> backgroundLayers, 
    std::vector<std::shared_ptr<ScreenLayer>> foregroundLayers,
    std::vector<std::shared_ptr<Connection>> connections
) 
:id(id)
,widthBlocks(widthBlocks)
,heightBlocks(heightBlocks)
,offsetX(0)
,offsetY(0)
,trainer(trainer)
,backgroundLayers(backgroundLayers)
,foregroundLayers(foregroundLayers)
{
    for (auto type : ALL_DIRECTION_TYPES) {
        connectionsByDirection.insert({type, std::vector<std::shared_ptr<Connection>> {}});
    }

    state.id = id;
    state.type = StateType::LAYOUT;

    for (auto c : connections) {
        connectionsByDirection.at(c->direction.getAsEnum()).push_back(c);
        connectionsByName.insert({c->transition.toAttribute, c});
    }
}

Layout::~Layout()
{
    for (auto layer : backgroundLayers) {
        layer->~ScreenLayer();
    }

    for (auto layer : foregroundLayers) {
        layer->~ScreenLayer();
    }
}

void Layout::init(int offsetX, int offsetY) {
    this->offsetX = offsetX;
    this->offsetY = offsetY;

    for (auto layer : backgroundLayers) {
        layer->init(this->offsetX, this->offsetY);
    }

    for (auto layer : foregroundLayers) {
        layer->init(this->offsetX, this->offsetY);
    }
}


std::vector<std::shared_ptr<ScreenLayer>> Layout::getBackgroundLayers()
{
    return backgroundLayers;
}

std::vector<std::shared_ptr<ScreenLayer>> Layout::getForegroundLayers() 
{
    return foregroundLayers;
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
    }
}

std::optional<StateTransition> Layout::handleWASDMovement(Direction dir) 
{
    int collisionHeight = 0;

    auto edge = trainer->getEdge(dir);
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
            for (auto c : connectionsByDirection.at(DirectionType::UP)) {
                auto cEdge = c->edge;
                if (edge.first.y <= cEdge.first.y && 
                    edge.first.x >= cEdge.first.x &&
                    edge.second.x <= cEdge.second.x) {
                    transition = c->transition;
                }
            }
        } else if (dirEnum == DirectionType::DOWN) {
            for (auto c : connectionsByDirection.at(DirectionType::DOWN)) {
                auto cEdge = c->edge;
                if (edge.first.y >= cEdge.first.y && 
                    edge.first.x >= cEdge.first.x &&
                    edge.second.x <= cEdge.second.x) {
                    transition = c->transition;
                }
            }
        } else if (dirEnum == DirectionType::LEFT) {
            for (auto c : connectionsByDirection.at(DirectionType::LEFT)) {
                auto cEdge = c->edge;
                if (edge.first.x <= cEdge.first.x && 
                    edge.first.y >= cEdge.first.y &&
                    edge.second.y <= cEdge.second.y) {
                    transition = c->transition;
                }
            }
        } else if (dirEnum == DirectionType::RIGHT) {
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

State Layout::getState()
{
    return state;
}