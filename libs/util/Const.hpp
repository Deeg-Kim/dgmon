#ifndef UTIL_CONST_H
#define UTIL_CONST_H

namespace DGMon {
    const int TILE_MAP_TILE_SIZE = 32;
    const int TILE_SIZE = 32;
    const int BLOCK_SIZE = 64;
    
    const int CHARACTER_BLOCK_SIZE_X_OFFSET = 16;
    const int CHARACTER_BLOCK_SIZE_Y_OFFSET = 24;
    const int CHARACTER_BLOCK_SIZE_X = 32;
    const int CHARACTER_BLOCK_SIZE_Y = 48;
    const int CHARACTER_HITBOX_SIZE_X_OFFSET = 18;
    const int CHARACTER_HITBOX_SIZE_Y_OFFSET = 24;

    const int WIDTH_BLOCKS = 40;
    const int HEIGHT_BLOCKS = 22;

    const int INFINITE_HEIGHT = 999;

    enum TextureSource {
        NO_TEXTURE,
        OUTSIDE
    };
}

#endif