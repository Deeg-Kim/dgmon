#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <set>
#include "util/Util.hpp"
#include "Tile.hpp"

namespace DGMon {
    class Block {
        public:
            Block(std::vector<Tile> tiles, std::vector<Tile> tiles3d, std::vector<int> heights);
            ~Block();
            std::vector<sf::Vertex> getVertices(int initX, int initY);
            std::vector<sf::Vertex> get3dVertices(int initX, int initY);
            std::string name;
        private:
            std::vector<Tile> tiles;
            std::vector<Tile> tiles3d;
            std::vector<int> heights;
    };
};

#endif