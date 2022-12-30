#ifndef TILE_H
#define TILE_H

#include <memory>
#include "util/Const.hpp"
#include "util/Util.hpp"
#include <SFML/Graphics.hpp>

namespace DGMon {
    struct Tile {
        Tile(TextureSource source, int texX, int texY, sf::Color color)
        :source(source)
        ,texX(texX)
        ,texY(texY)
        ,color(color)
        {}
        TextureSource source;
        int texX;
        int texY;
        sf::Color color;
    };

    const Tile TILE_NONE {OUTSIDE, 0, 0, sf::Color(0, 0, 0, 0)}; 
    const std::shared_ptr<Tile> TILE_NONE_PTR = std::make_shared<Tile>(OUTSIDE, 0, 0, sf::Color(0, 0, 0, 0));
};

#endif