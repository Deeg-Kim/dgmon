#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <set>
#include "util/Util.hpp"
#include "Tile.hpp"

namespace DGMon {
    class Block {
        public:
            Block(std::vector<Tile> tiles, int height);
            ~Block();
            std::vector<sf::Vertex> getVertecies(int initX, int initY);
            std::string name;
        private:
            std::vector<Tile> tiles;
            int height;
    };
};

#endif