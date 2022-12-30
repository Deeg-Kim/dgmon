#ifndef LAYOUT_H
#define LAYOUT_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <util/Util.hpp>
#include "Trainer.hpp"
#include "Zone.hpp"

namespace DGMon {
    class Layout {
        public:
            Layout(Zone layer0, Zone layer1);
            ~Layout();
            void draw(sf::RenderWindow* window);
            void movePrimaryPlayer(Direction dir);
        private:
            Zone layer0;
            Zone layer1;
            Trainer trainer;
            std::pair<sf::Vector2i, sf::Vector2i> getTrainerEdge(Direction dir);
    };
};

#endif