#include "Trainer.hpp"
#include "SFML/System/Vector2.hpp"
#include <utility>

using namespace DGMon;

Trainer::Trainer(int x, int y)
:vertices(sf::VertexArray ())
,texture(sf::Texture ())
,spriteSpeed(16.f) 
,height(0)
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

void Trainer::load() 
{
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

void Trainer::move(Direction direction) 
{
    positionX += direction.getAsVector().x * spriteSpeed;
    positionY += direction.getAsVector().y * spriteSpeed;
    tileState = (tileState + 1) % 4;
    auto dirEnum = direction.getAsEnum();
    switch (dirEnum) {
        case DirectionType::UP: 
            tileRow = 3;
            break;
        case DirectionType::DOWN: case DirectionType::NONE:
            tileRow = 0;
            break;
        case DirectionType::LEFT:
            tileRow = 1;
            break;
        case DirectionType::RIGHT:
            tileRow = 2;
            break;
    }

    load();
}

void Trainer::setLocation(int x, int y) {
    positionX = x;
    positionY = y;
}

int Trainer::getHeight() 
{
    return height;
}

std::pair<sf::Vector2i, sf::Vector2i> Trainer::getBoundary() 
{
    return std::make_pair(
        sf::Vector2i (positionX - CHARACTER_HITBOX_SIZE_X_OFFSET, positionY - CHARACTER_HITBOX_SIZE_Y_OFFSET), 
        sf::Vector2i (positionX + CHARACTER_HITBOX_SIZE_X_OFFSET, positionY + CHARACTER_HITBOX_SIZE_Y_OFFSET)
    );
}

void Trainer::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(vertices, states);
}