#ifndef TRAINER_H
#define TRAINER_H

#include "util/Util.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace DGMon {
    class Trainer : public sf::Drawable, public sf::Transformable, public Movable, public Collidable {
        public:
            Trainer(int x, int y);
            ~Trainer();
            void refresh();
            void move(Direction direction);
            int getHeight();
            std::pair<sf::Vector2i, sf::Vector2i> getBoundary();
        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            sf::VertexArray vertices;
            sf::Texture texture;
            float spriteSpeed;
            int height;
            int positionX;
            int positionY;
            int tileState;
            int tileRow;
            sf::Vector2u tileSize;
            int blockSize;
    };
};

#endif