#ifndef MOVABLE_H
#define MOVABLE_H

#include "Direction.hpp"

namespace DGMon {
    class Movable {
        virtual void move(Direction direction) {};
    };
};

#endif