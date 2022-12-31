add_library(
    DGMonLibrary
    "${CMAKE_CURRENT_SOURCE_DIR}/util/Collidable.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/Const.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/Direction.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/Direction.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/Movable.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/Util.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/game/Tile.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Block.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Block.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/ZoneLayer.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/ZoneLayer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Trainer.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Trainer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Layout.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Layout.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Game.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/data/LayoutLoader.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/data/LayoutLoader.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/state/StateManager.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/state/StateManager.cpp"
    
)
target_link_libraries(DGMonLibrary PRIVATE jsoncpp_lib sfml-graphics)
target_include_directories(DGMonLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")