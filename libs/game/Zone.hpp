#ifndef ZONE_H
#define ZONE_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include "util/Util.hpp"
#include "TextureLoader.hpp"
#include "Block.hpp"
#include "Tile.hpp"

namespace DGMon {
    class Zone : public sf::Drawable, public sf::Transformable {
        public:
            Zone(std::vector<Block> blocks);
            ~Zone();
            void load();
        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            std::vector<Block> blocks;
            sf::Texture texture;
            sf::VertexArray vertices;
    };
};

#endif