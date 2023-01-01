#ifndef LAYOUT_H
#define LAYOUT_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <util/Util.hpp>
#include "Trainer.hpp"
#include "ZoneLayer.hpp"
#include "Connection.hpp"
#include "state/Screen.hpp"
#include "state/State.hpp"
#include "util/Direction.hpp"

namespace DGMon {
    class Layout : public Screen {
        public:
            Layout(
                std::string id,
                int widthBlocks,
                int heightBlocks,
                std::vector<std::shared_ptr<ZoneLayer>> backgroundLayers, 
                std::vector<std::shared_ptr<ZoneLayer>> foregroundLayers,
                std::vector<std::shared_ptr<Connection>> connections
            );
            ~Layout();
            void draw(sf::RenderWindow* window) override;
            void handlePreviousTransition(StateTransition transition) override;
            std::optional<StateTransition> handleWASDMovement(Direction dir) override;
            State getState() override;
        private:
            std::string id;
            int widthBlocks;
            int heightBlocks;
            sf::View view;
            std::vector<std::shared_ptr<ZoneLayer>> backgroundLayers;
            std::vector<std::shared_ptr<ZoneLayer>> foregroundLayers;
            std::unordered_map<std::string, std::shared_ptr<Connection>> connectionsByName;
            std::unordered_map<DirectionType, std::vector<std::shared_ptr<Connection>>> connectionsByDirection;
            std::shared_ptr<Trainer> trainer;
            std::pair<sf::Vector2i, sf::Vector2i> getTrainerEdge(Direction dir);
            State state;
    };
};

#endif