#ifndef TILE_H
#define TILE_H

#include <memory>
#include "util/Util.hpp"
#include <SFML/Graphics.hpp>

namespace DGMon {
    struct Tile {
        Tile(std::string source, int texX, int texY, sf::Color color)
        :source(source)
        ,texX(texX)
        ,texY(texY)
        ,color(color)
        {}
        std::string source;
        int texX;
        int texY;
        sf::Color color;
    };

    const Tile TILE_NONE {"tilesets/Outside", 0, 0, sf::Color(0, 0, 0, 0)}; 
};

#endif