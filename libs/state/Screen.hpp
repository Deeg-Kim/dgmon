#ifndef SCREEN_H
#define SCREEN_H

#include "state/State.hpp"
#include "state/StateTransition.hpp"
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
            virtual State getState()
            {
                return {"", std::unordered_map<StateTransition, State> ()};
            }
            
    };
};

#endif