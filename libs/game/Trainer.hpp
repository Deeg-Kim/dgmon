#ifndef TRAINER_H
#define TRAINER_H

#include "util/Util.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace DGMon {
    class Trainer : public sf::Drawable, public sf::Transformable, public Movable, public Collidable {
        public:
            Trainer(int x, int y, std::shared_ptr<sf::View> view);
            ~Trainer();
            void load();
            void move(Direction direction) override;
            void setLocation(int x, int y) override;
            int getHeight() override;
            std::pair<sf::Vector2i, sf::Vector2i> getEdge(Direction dir) override;
            float spriteSpeed;
        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::shared_ptr<sf::View> view;
            sf::VertexArray vertices;
            sf::Texture texture;
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