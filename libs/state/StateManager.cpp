#include "StateManager.hpp"
#include "state/StateTransition.hpp"

using namespace DGMon;

StateManager::StateManager(sf::RenderWindow* window, std::string initialScreenID)
:window(window)
{
    layoutLoader = std::make_unique<LayoutLoader>();
    screen = layoutLoader->getLayout(initialScreenID);
}

void StateManager::render()
{
    screen->draw(window);
}

void StateManager::handleWASDMovement(Direction dir) {
    auto transition = screen->handleWASDMovement(dir);

    if (transition.has_value()) {
        // if (transition->type == StateTransitionType::CONNECT) {
        //     if (transition->destinationType == StateType::LAYOUT) {
                screen = layoutLoader->getLayout(transition->attribute);
        //     }
        // }
    }
}