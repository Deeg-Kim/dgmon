#include "Trainer.hpp"

using namespace DGMon;

Trainer::Trainer(int x, int y)
:vertices(sf::VertexArray ())
,texture(sf::Texture ())
,spriteSpeed(7.f)
,positionX(x)
,positionY(y)
,tileState(0)
,tileRow(0)
,tileSize(sf::Vector2u {32, 48})
{
    if (!texture.loadFromFile("assets/characters/player_m.png")) {
        std::cerr << "Failed to load trainer texture\n";
    }
    
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(4);
}

Trainer::~Trainer() 
{
}

void Trainer::refresh() {
    sf::Vertex* vert = &vertices[0];

    vert[0].position = sf::Vector2f(positionX - CHARACTER_BLOCK_SIZE_X_OFFSET, positionY - CHARACTER_BLOCK_SIZE_Y_OFFSET);
    vert[1].position = sf::Vector2f(positionX + CHARACTER_BLOCK_SIZE_X_OFFSET, positionY - CHARACTER_BLOCK_SIZE_Y_OFFSET);
    vert[2].position = sf::Vector2f(positionX + CHARACTER_BLOCK_SIZE_X_OFFSET, positionY + CHARACTER_BLOCK_SIZE_Y_OFFSET);
    vert[3].position = sf::Vector2f(positionX - CHARACTER_BLOCK_SIZE_X_OFFSET, positionY + CHARACTER_BLOCK_SIZE_Y_OFFSET);

    vert[0].texCoords = sf::Vector2f(tileState * tileSize.x, tileRow * tileSize.y);
    vert[1].texCoords = sf::Vector2f((tileState + 1) * tileSize.x, tileRow * tileSize.y);
    vert[2].texCoords = sf::Vector2f((tileState + 1) * tileSize.x, (tileRow + 1) * tileSize.y);
    vert[3].texCoords = sf::Vector2f(tileState * tileSize.x, (tileRow + 1) * tileSize.y);
}

void Trainer::move(Direction direction) {
    positionX += direction.getAsVector().x * spriteSpeed;
    positionY += direction.getAsVector().y * spriteSpeed;
    tileState = (tileState + 1) % 4;
    auto dirEnum = direction.getAsEnum();
    switch (dirEnum) {
        case UP: 
            tileRow = 3;
            break;
        case DOWN: case NONE:
            tileRow = 0;
            break;
        case LEFT:
            tileRow = 1;
            break;
        case RIGHT:
            tileRow = 2;
            break;
    }

    refresh();
}

void Trainer::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(vertices, states);
}