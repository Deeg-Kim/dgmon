#ifndef LAYOUT_H
#define LAYOUT_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <util/Util.hpp>
#include "Trainer.hpp"
#include "ScreenLayer.hpp"
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
                std::shared_ptr<Trainer> trainer,
                std::vector<std::shared_ptr<ScreenLayer>> backgroundLayers, 
                std::vector<std::shared_ptr<ScreenLayer>> foregroundLayers,
                std::vector<std::shared_ptr<Connection>> connections
            );
            ~Layout();
            void init(int offsetX, int offsetY);
            std::vector<std::shared_ptr<ScreenLayer>> getBackgroundLayers() override;
            std::vector<std::shared_ptr<ScreenLayer>> getForegroundLayers() override; 
            void handlePreviousTransition(StateTransition transition) override;
            std::optional<StateTransition> handleWASDMovement(Direction dir) override;
            State getState() override;

            std::string id;
            int widthBlocks;
            int heightBlocks;
            int offsetX;
            int offsetY;
            std::unordered_map<DirectionType, std::vector<std::shared_ptr<Connection>>> connectionsByDirection;
        private:
            std::shared_ptr<Trainer> trainer;
            std::vector<std::shared_ptr<ScreenLayer>> backgroundLayers;
            std::vector<std::shared_ptr<ScreenLayer>> foregroundLayers;
            std::unordered_map<std::string, std::shared_ptr<Connection>> connectionsByName;
            State state;
    };
};

#endif