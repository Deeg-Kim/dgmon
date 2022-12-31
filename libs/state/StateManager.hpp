#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "data/LayoutLoader.hpp"
#include "state/Screen.hpp"
#include "state/State.hpp"
#include "state/StateTransition.hpp"
#include "util/Util.hpp"
#include <memory>
#include <unordered_map>
#include <optional>
#include <SFML/Graphics.hpp>

namespace DGMon {
    class StateManager {
        public:
            StateManager(sf::RenderWindow* window, std::string initialScreenID);
            void render();
            void handleWASDMovement(Direction dir);
        private:
            sf::RenderWindow* window;
            std::unique_ptr<LayoutLoader> layoutLoader;
            std::shared_ptr<Screen> screen;
    };
};

#endif