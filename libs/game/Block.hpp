#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <set>
#include "util/Util.hpp"
#include "Tile.hpp"

namespace DGMon {
    class Block {
        public:
            Block(std::string name, std::vector<std::shared_ptr<Tile>> tiles, std::vector<int> heights);
            ~Block();
            std::vector<sf::Vertex> getVertices(int initX, int initY);
            std::string name;
            std::vector<int> heights;
            std::vector<std::shared_ptr<Tile>> tiles;
    };
};

#endif