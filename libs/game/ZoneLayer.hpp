#ifndef ZONE_H
#define ZONE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <memory>

#include <SFML/Graphics.hpp>
#include "util/Util.hpp"
#include "Block.hpp"
#include "Tile.hpp"

namespace DGMon {
    class ZoneLayer : public sf::Drawable, public sf::Transformable {
        public:
            ZoneLayer(int widthBlocks, int heightBlocks, std::vector<std::shared_ptr<Block>> blocks, sf::Texture texture);
            ~ZoneLayer();
            void load();
            int getMaxHeight(std::pair<sf::Vector2i, sf::Vector2i> edge, Direction dir);
        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            int widthBlocks;
            int heightBlocks;
            std::vector<std::shared_ptr<Block>> blocks;
            sf::Texture texture;
            sf::VertexArray vertices;
    };
};

#endif