#ifndef SCREEN_H
#define SCREEN_H

#include "state/State.hpp"
#include "state/StateTransition.hpp"
#include "util/Util.hpp"
#include "game/ScreenLayer.hpp"
#include <vector>
#include <optional>
#include <unordered_map>

namespace DGMon {
    class Screen {
        public:
            virtual std::optional<StateTransition> handleWASDMovement(Direction dir)
            {
                return std::nullopt;
            }
            virtual void handlePreviousTransition(StateTransition transition) {}
            virtual State getState()
            {
                return {""};
            }
            virtual std::vector<std::shared_ptr<ScreenLayer>> getBackgroundLayers() 
            {
                return std::vector<std::shared_ptr<ScreenLayer>> ();
            }

            virtual std::vector<std::shared_ptr<ScreenLayer>> getForegroundLayers() 
            {
                return std::vector<std::shared_ptr<ScreenLayer>> ();
            }
            
    };
};

#endif