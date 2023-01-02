#include "Trainer.hpp"
#include "SFML/System/Vector2.hpp"
#include "util/Const.hpp"
#include <utility>

using namespace DGMon;

Trainer::Trainer(int x, int y, std::shared_ptr<sf::View> view)
:view(view)
,vertices(sf::VertexArray ())
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

    view->setCenter(sf::Vector2f(positionX, positionY));
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

    load();
}

int Trainer::getHeight() 
{
    return height;
}

std::pair<sf::Vector2i, sf::Vector2i> Trainer::getEdge(Direction dir) {
    auto boundary = std::make_pair(
        sf::Vector2i (positionX - CHARACTER_HITBOX_SIZE_X_OFFSET, positionY - CHARACTER_HITBOX_SIZE_Y_OFFSET), 
        sf::Vector2i (positionX + CHARACTER_HITBOX_SIZE_X_OFFSET, positionY + CHARACTER_HITBOX_SIZE_Y_OFFSET)
    );

    switch (dir.getAsEnum()) {
        case DirectionType::UP:
            return std::make_pair(sf::Vector2i (boundary.first.x, boundary.first.y),sf::Vector2i (boundary.second.x, boundary.first.y));
        case DirectionType::DOWN:
            return std::make_pair(sf::Vector2i (boundary.first.x, boundary.second.y),sf::Vector2i (boundary.second.x, boundary.second.y));
        case DirectionType::LEFT:
            return std::make_pair(sf::Vector2i (boundary.first.x, boundary.first.y), sf::Vector2i (boundary.first.x, boundary.second.y));
        case DirectionType::RIGHT:
            return std::make_pair(sf::Vector2i (boundary.second.x, boundary.first.y), sf::Vector2i (boundary.second.x, boundary.second.y));
        default:
            throw new std::invalid_argument("Unknown direction.");
    }
}

void Trainer::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(vertices, states);
}