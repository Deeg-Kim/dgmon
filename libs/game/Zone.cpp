#include "Zone.hpp"
#include "util/Const.hpp"

using namespace DGMon;

Zone::Zone(std::vector<std::shared_ptr<Block>> blocks, sf::Texture texture)
:blocks(blocks)
,vertices(sf::VertexArray ())
,texture(texture)
{
}

Zone::~Zone() 
{
    std::vector<std::shared_ptr<Block>>().swap(blocks);
    sf::Texture().swap(texture);
}

void Zone::load() 
{
    vertices.setPrimitiveType(sf::Quads);
    // 4 quds per tile, 4 tiles per block
    vertices.resize(WIDTH_BLOCKS * HEIGHT_BLOCKS * 4 * 4);

    for (int i = 0; i < WIDTH_BLOCKS; i++) {
        for (int j = 0; j < HEIGHT_BLOCKS; j++) {
            auto block = blocks.at(i + j * WIDTH_BLOCKS);
            for (auto v : block->getVertices(i * BLOCK_SIZE, j * BLOCK_SIZE)) {
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

    int tilesStartX = floor(static_cast<double>(edge.first.x) / TILE_MAP_TILE_SIZE);
    int tilesStartY = floor(static_cast<double>(edge.first.y) / TILE_MAP_TILE_SIZE);
    int tilesEndX = floor(static_cast<double>(edge.second.x) / TILE_MAP_TILE_SIZE);
    int tilesEndY = floor(static_cast<double>(edge.second.y) / TILE_MAP_TILE_SIZE);

    int max = 0;

    if (tilesStartX == tilesEndX) {
        for (int i = tilesStartY; i <= tilesEndY; i++) {
            int blockX = floor(static_cast<double>(tilesStartX) / 2);
            int blockY = floor(static_cast<double>(i) / 2);
            max = std::max(max, blocks.at(blockX + WIDTH_BLOCKS * blockY)->heights.at(getTileIdx(tilesStartX, i)));
        }
    } else if (tilesStartY == tilesEndY) {
        for (int i = tilesStartX; i <= tilesEndX; i++) {
            int blockX = floor(static_cast<double>(i) / 2);
            int blockY = floor(static_cast<double>(tilesStartY) / 2);
            max = std::max(max, blocks.at(blockX + WIDTH_BLOCKS * blockY)->heights.at(getTileIdx(i, tilesStartY)));
        }
    }

    return max;
}

void Zone::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(vertices, states);
}
