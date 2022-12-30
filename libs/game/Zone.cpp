#include "Zone.hpp"

using namespace DGMon;

Zone::Zone(std::vector<Block> blocks, sf::Texture texture)
:blocks(blocks)
,vertices(sf::VertexArray ())
,texture(texture)
{
}

Zone::~Zone() 
{
}

void Zone::load() 
{
    vertices.setPrimitiveType(sf::Quads);
    // 4 quds per tile, 4 tiles per block
    vertices.resize(WIDTH_BLOCKS * HEIGHT_BLOCKS * 4 * 4);

    for (int i = 0; i < WIDTH_BLOCKS; i++) {
        for (int j = 0; j < HEIGHT_BLOCKS; j++) {
            Block block = blocks.at(i + j * WIDTH_BLOCKS);
            for (auto v : block.getVertices(i * BLOCK_SIZE, j * BLOCK_SIZE)) {
                vertices.append(v);
            }
        }
    }
}

int getTileIdx(int x, int y) {
    int xR = x % 2;
    int yR = y % 2;

    if (xR == 0 && yR == 0) {
        return 0;
    } else if (xR == 1 && yR == 0) {
        return 1;
    } else if (xR == 0 && yR == 1) {
        return 2;
    } else {
        return 3;
    }
}

int Zone::getMaxHeight(std::pair<sf::Vector2i, sf::Vector2i> edge, Direction dir) {
    auto dirEnum = dir.getAsEnum();

    if ((dirEnum == UP && edge.first.y <= 0) || 
        (dirEnum == DOWN && edge.first.y >= 704) ||
        (dirEnum == LEFT && edge.first.x <= 0) ||
        (dirEnum == RIGHT && edge.first.x >= 1280)) {
        return INFINITE_HEIGHT;
    }

    int tilesX1 = floor(static_cast<double>(edge.first.x) / TILE_MAP_TILE_SIZE);
    int tilesY1 = floor(static_cast<double>(edge.first.y) / TILE_MAP_TILE_SIZE);
    int tilesX2 = floor(static_cast<double>(edge.second.x) / TILE_MAP_TILE_SIZE);
    int tilesY2 = floor(static_cast<double>(edge.second.y) / TILE_MAP_TILE_SIZE);

    int block1X = floor(static_cast<double>(tilesX1) / 2);
    int block1Y = floor(static_cast<double>(tilesY1) / 2);
    int block2X = floor(static_cast<double>(tilesX2) / 2);
    int block2Y = floor(static_cast<double>(tilesY2) / 2);

    int tile1Height = blocks.at(block1X + WIDTH_BLOCKS * block1Y).heights.at(getTileIdx(tilesX1, tilesY1));
    int tile2Height = blocks.at(block2X + WIDTH_BLOCKS * block2Y).heights.at(getTileIdx(tilesX2, tilesY2));

    return std::max(tile1Height, tile2Height);
}

void Zone::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(vertices, states);
}
