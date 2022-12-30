#ifndef ZONE_H
#define ZONE_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include "util/Util.hpp"
#include "Block.hpp"
#include "Tile.hpp"
#include "Trainer.hpp"

namespace DGMon {
    class Zone : public sf::Drawable, public sf::Transformable {
        public:
            Zone(std::vector<Block> blocks, sf::Texture texture, Trainer trainer);
            ~Zone();
            void load();
            Trainer trainer;
        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            std::vector<Block> blocks;
            sf::Texture texture;
            sf::VertexArray vertices;
    };
};

#endif