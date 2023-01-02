#include "ScreenLayer.hpp"
#include "util/Const.hpp"

using namespace DGMon;

ScreenLayer::ScreenLayer(
    int widthBlocks, 
    int heightBlocks,
    std::vector<std::shared_ptr<Block>> blocks, 
    std::shared_ptr<sf::Texture> texture)
:widthBlocks(widthBlocks)
,heightBlocks(heightBlocks)
,blocks(blocks)
,vertices(sf::VertexArray ())
,texture(texture)
{
}

ScreenLayer::~ScreenLayer() 
{
    std::vector<std::shared_ptr<Block>>().swap(blocks);
}

void ScreenLayer::init(int offsetX, int offsetY) 
{
    this->offsetX = offsetX;
    this->offsetY = offsetY;

    vertices.setPrimitiveType(sf::Quads);
    // 4 quds per tile, 4 tiles per block
    vertices.resize(widthBlocks * heightBlocks * 4 * 4);

    for (int i = 0; i < widthBlocks; i++) {
        for (int j = 0; j < heightBlocks; j++) {
            auto block = blocks.at(i + j * widthBlocks);
            for (auto v : block->getVertices(i * BLOCK_SIZE + this->offsetX, j * BLOCK_SIZE + this->offsetY)) {
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

int ScreenLayer::getMaxHeight(std::pair<sf::Vector2i, sf::Vector2i> edge, Direction dir) {
    auto dirEnum = dir.getAsEnum();

    if ((dirEnum == DirectionType::UP && edge.first.y <= 0) || 
        (dirEnum == DirectionType::DOWN && edge.first.y >= heightBlocks * BLOCK_SIZE) ||
        (dirEnum == DirectionType::LEFT && edge.first.x <= 0) ||
        (dirEnum == DirectionType::RIGHT && edge.first.x >= widthBlocks * BLOCK_SIZE)) {
        return INFINITE_HEIGHT;
    }

    int tilesStartX = floor(static_cast<double>(edge.first.x) / TILE_MAP_TILE_SIZE);
    int tilesStartY = floor(static_cast<double>(edge.first.y) / TILE_MAP_TILE_SIZE);
    int tilesEndX = floor(static_cast<double>(edge.second.x) / TILE_MAP_TILE_SIZE);
    int tilesEndY = floor(static_cast<double>(edge.second.y) / TILE_MAP_TILE_SIZE);

    int max = 0;

    if (tilesStartX == tilesEndX) {
        for (int i = tilesStartY; i < tilesEndY; i++) {
            int blockX = floor(static_cast<double>(tilesStartX) / 2);
            int blockY = floor(static_cast<double>(i) / 2);
            max = std::max(max, blocks.at(blockX + widthBlocks * blockY)->heights.at(getTileIdx(tilesStartX, i)));
        }
    } else if (tilesStartY == tilesEndY) {
        for (int i = tilesStartX; i < tilesEndX; i++) {
            int blockX = floor(static_cast<double>(i) / 2);
            int blockY = floor(static_cast<double>(tilesStartY) / 2);
            max = std::max(max, blocks.at(blockX + widthBlocks * blockY)->heights.at(getTileIdx(i, tilesStartY)));
        }
    }

    return max;
}

void ScreenLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &*texture;
    target.draw(vertices, states);
}
