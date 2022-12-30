#ifndef ZONE_H
#define ZONE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include "util/Util.hpp"
#include "Block.hpp"
#include "Tile.hpp"

namespace DGMon {
    class Zone : public sf::Drawable, public sf::Transformable {
        public:
            Zone(std::vector<Block> blocks, sf::Texture texture);
            ~Zone();
            void load();
            int getMaxHeight(std::pair<sf::Vector2i, sf::Vector2i> edge, Direction dir);
        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            std::vector<Block> blocks;
            sf::Texture texture;
            sf::VertexArray vertices;
    };
};

#endif