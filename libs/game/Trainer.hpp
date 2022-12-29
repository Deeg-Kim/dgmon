#ifndef TRAINER_H
#define TRAINER_H
#include "util/Util.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace DGMon {
    class Trainer : public sf::Drawable, public sf::Transformable {
        public:
            Trainer(int x, int y);
            ~Trainer();
            void refresh();
            void move(Direction direction);
        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            sf::VertexArray vertices;
            sf::Texture texture;
            float spriteSpeed;
            int positionX;
            int positionY;
            int tileState;
            int tileRow;
            sf::Vector2u tileSize;
            int blockSize;
    };
};

#endif