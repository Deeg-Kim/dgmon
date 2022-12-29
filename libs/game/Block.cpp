#include "Block.hpp"

using namespace DGMon;

Block::Block(std::string name, std::vector<Tile> tiles, int height)
:name(name)
,tiles(tiles)
,height(height)
{
}

Block::~Block() 
{
}

std::vector<sf::Vertex> Block::getVertecies(int initX, int initY) {
    // one quad per tile
    std::vector<sf::Vertex> res (4 * 4);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            auto tile = tiles.at(i + j * 2);
            sf::Vertex v1 (
                sf::Vector2f(i * TILE_SIZE + initX, j * TILE_SIZE + initY), 
                tile.color, 
                sf::Vector2f(tile.texX * TILE_MAP_TILE_SIZE, tile.texY * TILE_MAP_TILE_SIZE)
            );

            sf::Vertex v2 (
                sf::Vector2f((i + 1) * TILE_SIZE + initX, j * TILE_SIZE + initY),
                tile.color,
                sf::Vector2f((tile.texX + 1) * TILE_MAP_TILE_SIZE, tile.texY * TILE_MAP_TILE_SIZE)
            );

            sf::Vertex v3 (
                sf::Vector2f((i + 1) * TILE_SIZE + initX, (j + 1) * TILE_SIZE + initY),
                tile.color,
                sf::Vector2f((tile.texX + 1) * TILE_MAP_TILE_SIZE, (tile.texY + 1) * TILE_MAP_TILE_SIZE)
            );

            sf::Vertex v4 (
                sf::Vector2f(i * TILE_SIZE + initX, (j + 1) * TILE_SIZE + initY),
                tile.color,
                sf::Vector2f(tile.texX * TILE_MAP_TILE_SIZE, (tile.texY + 1) * TILE_MAP_TILE_SIZE)
            );

            res.push_back(v1);
            res.push_back(v2);
            res.push_back(v3);
            res.push_back(v4);
        }
    }

    return res;
}