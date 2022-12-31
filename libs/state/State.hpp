#ifndef STATE_H
#define STATE_H

#include "state/StateTransition.hpp"
#include <string>
#include <unordered_map>

namespace DGMon {
    struct State {
        std::string id;
        StateType type;
    };
}

#endif