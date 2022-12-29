#ifndef TILE_H
#define TILE_H

#include "util/Util.hpp"
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Color.hpp"

namespace DGMon {
    struct Tile {
        TextureSource source;
        int texX;
        int texY;
        sf::Color color;
    };

    const Tile GRASS_1 {OUTSIDE, 1, 0, sf::Color::White}; 
    const Tile GRASS_2 {OUTSIDE, 2, 0, sf::Color::White}; 
    const Tile GRASS_3 {OUTSIDE, 3, 0, sf::Color::White}; 
    const Tile GRASS_4 {OUTSIDE, 4, 0, sf::Color::White}; 
};

#endif