#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "state/State.hpp"
#include "state/StateTransition.hpp"
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace DGMon {
    class StateManager {
        public:
            StateManager(sf::RenderWindow* window);
        private:
            std::unordered_map<StateTransition, State> curTransitions;
            sf::RenderWindow* window;
    };
};

#endif