#ifndef TILE_H
#define TILE_H

#include "util/Const.hpp"
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

    const Tile TILE_NONE {OUTSIDE, 0, 0, sf::Color(0, 0, 0, 0)}; 
};

#endif