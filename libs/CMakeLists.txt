add_library(
    DGMonLibrary
    "${CMAKE_CURRENT_SOURCE_DIR}/game/TextureLoader.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/TextureLoader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Tile.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Block.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Block.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Zone.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Zone.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Trainer.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Trainer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/Game.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/Direction.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/Direction.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/Util.hpp"
)
target_link_libraries(DGMonLibrary PRIVATE sfml-graphics)
target_include_directories(DGMonLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")