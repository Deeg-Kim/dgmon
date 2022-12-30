#ifndef LAYOUT_H
#define LAYOUT_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <util/Util.hpp>
#include "Trainer.hpp"
#include "Zone.hpp"

namespace DGMon {
    class Layout {
        public:
            Layout(std::shared_ptr<Zone> layer0, std::shared_ptr<Zone> layer1, std::shared_ptr<Zone> layer2);
            ~Layout();
            void draw(sf::RenderWindow* window);
            void movePrimaryPlayer(Direction dir);
        private:
            std::shared_ptr<Zone> layer0;
            std::shared_ptr<Zone> layer1;
            std::shared_ptr<Zone> layer2;
            std::shared_ptr<Trainer> trainer;
            std::pair<sf::Vector2i, sf::Vector2i> getTrainerEdge(Direction dir);
    };
};

#endif