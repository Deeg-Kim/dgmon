#include "StateManager.hpp"
#include "state/StateTransition.hpp"

using namespace DGMon;

StateManager::StateManager(sf::RenderWindow* window, std::string initialScreenID)
:window(window)
{
    view = std::make_shared<sf::View>(sf::Vector2f(static_cast<double>(12) * BLOCK_SIZE / 2, static_cast<double>(11) * BLOCK_SIZE / 2), sf::Vector2f(800.f, 600.f));
    trainer = std::make_shared<Trainer>(static_cast<double>(12) * BLOCK_SIZE / 2, static_cast<double>(11) * BLOCK_SIZE / 2, view);
    trainer->load();
    window->setView(*view);
    textureLoader = std::make_shared<TextureLoader>();
    layoutLoader = std::make_unique<LayoutLoader>(view, textureLoader);
    screens = layoutLoader->loadLayout(initialScreenID, 0, 0, trainer);
}

void StateManager::render()
{
    window->setView(*view);
    for (auto screen : screens->adjacent) {
        for (auto layer : screen.second->getBackgroundLayers()) {
            window->draw(*layer);
        }
    }
    for (auto layer : screens->primary->getBackgroundLayers()) {
        window->draw(*layer);
    }
    window->draw(*trainer);
    for (auto screen : screens->adjacent) {
        for (auto layer : screen.second->getForegroundLayers()) {
            window->draw(*layer);
        }
    }
    for (auto layer : screens->primary->getForegroundLayers()) {
        window->draw(*layer);
    }
}

void StateManager::handleWASDMovement(Direction dir) {
    auto transition = screens->primary->handleWASDMovement(dir);

    if (transition.has_value()) {
        if (transition->type == StateTransitionType::CONNECT) {
            if (transition->destinationType == StateType::LAYOUT) {
                auto adj = screens->adjacent.at(transition->toAttribute);
                screens = layoutLoader->loadLayout(adj->id, adj->offsetX, adj->offsetY, trainer);
            }
        }
    }
}