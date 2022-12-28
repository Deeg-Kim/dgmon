#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Color.hpp"
#include "TextureLoader.hpp"

namespace DGMon {
    struct Tile {
        TextureSource source;
        int texX;
        int texY;
        sf::Color color;
    };

    const Tile GRASS_1 {PRIMARY_GENERAL, 9, 24, sf::Color(54, 196, 74)}; 
    const Tile GRASS_2 {PRIMARY_GENERAL, 10, 24, sf::Color(54, 196, 74)}; 
    const Tile GRASS_3 {PRIMARY_GENERAL, 9, 25, sf::Color(54, 196, 74)}; 
    const Tile GRASS_4 {PRIMARY_GENERAL, 10, 25, sf::Color(54, 196, 74)}; 
};

#endif