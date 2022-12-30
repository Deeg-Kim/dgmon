#include "Zone.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"
#include "util/Const.hpp"

using namespace DGMon;

Zone::Zone(std::vector<Block> blocks, sf::Texture texture, Trainer trainer)
:blocks(blocks)
,vertices(sf::VertexArray ())
,texture(texture)
,trainer(trainer)
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

void Zone::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(vertices, states);
}
