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
,tileSize(sf::Vector2u {64, 64})
,blockSize(64)
{
    if (!texture.loadFromFile("assets/textures/m-walk.png")) {
        std::cerr << "Failed to load trainer texture\n";
    }
    
    this->vertices.setPrimitiveType(sf::Quads);
    this->vertices.resize(4);
}

Trainer::~Trainer() 
{
}

void Trainer::refresh() {
    sf::Vertex* mainVertex = &vertices[0];

    mainVertex[0].position = sf::Vector2f(positionX - blockSize / 2, positionY - blockSize / 2);
    mainVertex[1].position = sf::Vector2f(positionX + blockSize / 2, positionY - blockSize / 2);
    mainVertex[2].position = sf::Vector2f(positionX + blockSize / 2, positionY + blockSize / 2);
    mainVertex[3].position = sf::Vector2f(positionX - blockSize / 2, positionY + blockSize / 2);

    mainVertex[0].texCoords = sf::Vector2f(tileState * tileSize.x, tileRow * tileSize.y);
    mainVertex[1].texCoords = sf::Vector2f((tileState + 1) * tileSize.x, tileRow * tileSize.y);
    mainVertex[2].texCoords = sf::Vector2f((tileState + 1) * tileSize.x, (tileRow + 1) * tileSize.y);
    mainVertex[3].texCoords = sf::Vector2f(tileState * tileSize.x, (tileRow + 1) * tileSize.y);
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