#ifndef SCREEN_H
#define SCREEN_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "state/State.hpp"
#include "state/StateTransition.hpp"
#include "util/Direction.hpp"
#include "util/Util.hpp"
#include <optional>
#include <unordered_map>

namespace DGMon {
    class Screen {
        public:
            virtual std::optional<StateTransition> handleWASDMovement(Direction dir)
            {
                return std::nullopt;
            }
            virtual void draw(sf::RenderWindow* window) {}
            virtual void handlePreviousTransition(StateTransition transition) {}
            virtual State getState()
            {
                return {""};
            }
            
    };
};

#endif