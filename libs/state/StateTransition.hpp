#ifndef STATE_TRANSITION_H
#define STATE_TRANSITION_H

#include <functional>
#include <string>

namespace DGMon {
    enum class StateType {
        LAYOUT
    };

    enum class StateTransitionType {
        CONNECT, WARP
    };

    struct StateTransition {
        StateTransitionType type;
        std::string attribute;
        StateType destinationType;

        bool operator==(const StateTransition& other) const 
        {
            return type == other.type && attribute == other.attribute;
        }
    };
};

template<>
struct std::hash<DGMon::StateTransitionType> {
    std::size_t operator()(DGMon::StateTransitionType const& stt) const noexcept
    {
        if (stt == DGMon::StateTransitionType::CONNECT) {
            return std::hash<int>{}(0);
        } else if (stt == DGMon::StateTransitionType::WARP) {
            return std::hash<int>{}(1);
        } else {
            return std::hash<int>{}(-1);
        }
    }
};

template<>
struct std::hash<DGMon::StateTransition> {
    std::size_t operator()(DGMon::StateTransition const& st) const noexcept
    {
        std::size_t h1 = std::hash<DGMon::StateTransitionType>{}(st.type);
        std::size_t h2 = std::hash<std::string>{}(st.attribute);

        return ((h1 ^ (h2 << 1)) >> 1);
    }
};

#endif