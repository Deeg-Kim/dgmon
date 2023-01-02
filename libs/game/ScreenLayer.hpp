#ifndef ZONE_H
#define ZONE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <memory>

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "util/Util.hpp"
#include "Block.hpp"
#include "Tile.hpp"

namespace DGMon {
    class ScreenLayer : public sf::Drawable, public sf::Transformable {
        public:
            ScreenLayer(int widthBlocks, int heightBlocks, std::vector<std::shared_ptr<Block>> blocks, std::shared_ptr<sf::Texture> texture);
            ~ScreenLayer();
            void init(int offsetX, int offsetY);
            int getMaxHeight(std::pair<sf::Vector2i, sf::Vector2i> edge, Direction dir);
        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            int widthBlocks;
            int heightBlocks;
            int offsetX;
            int offsetY;
            std::vector<std::shared_ptr<Block>> blocks;
            std::shared_ptr<sf::Texture> texture;
            sf::VertexArray vertices;
    };
};

#endif