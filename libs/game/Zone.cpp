#include "Zone.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "game/TextureLoader.hpp"
#include "util/Const.hpp"

using namespace DGMon;

Zone::Zone(std::vector<Block> blocks)
:blocks(blocks)
,texture(sf::Texture ())
{
    TextureSource source = PRIMARY_GENERAL;

    switch (source) {
        case PRIMARY_GENERAL:
            if (!texture.loadFromFile("assets/tilesets/primary/general/tiles.png")) {
                std::cerr << "Failed to load primary general texture\n";
            }
            break;
        default:
            throw std::invalid_argument("Unknown texture source.");
    }

    sf::VertexArray vertices;
}

Zone::~Zone() 
{
}

void Zone::load() 
{
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(WIDTH_BLOCKS * HEIGHT_BLOCKS * 4 * 4);

    for (int i = 0; i < WIDTH_BLOCKS; i++) {
        for (int j = 0; j < HEIGHT_BLOCKS; j++) {
             // TODO: Fix when blocks are defined better
            Block cur = blocks.at(0);
            for (auto v : cur.getVertecies(i * BLOCK_SIZE, j * BLOCK_SIZE)) {
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
