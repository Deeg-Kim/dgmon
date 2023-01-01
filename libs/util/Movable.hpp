#ifndef MOVABLE_H
#define MOVABLE_H

#include "Direction.hpp"

namespace DGMon {
    class Movable {
        virtual void move(Direction direction) {};
        virtual void setLocation(int x, int y) {};
    };
};

#endif