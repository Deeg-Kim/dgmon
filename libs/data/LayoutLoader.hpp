#ifndef LAYOUT_LOADER_H
#define LAYOUT_LOADER_H

#include "game/Game.hpp"
#include "TextureLoader.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <memory>
#include <json/json.h>
#include <SFML/Graphics.hpp>

namespace DGMon {
    struct LayoutLoad {
        LayoutLoad(std::shared_ptr<Layout> primary, std::unordered_map<std::string, std::shared_ptr<Layout>> adjacent)
        :primary(primary)
        ,adjacent(adjacent)
        {}
        std::shared_ptr<Layout> primary;
        std::unordered_map<std::string, std::shared_ptr<Layout>> adjacent;
    };

    class LayoutLoader {
        public:
            LayoutLoader(std::shared_ptr<sf::View> view, std::shared_ptr<TextureLoader> textureLoader);
            ~LayoutLoader();
            std::shared_ptr<LayoutLoad> loadLayout(std::string zoneName, int offsetX, int offsetY, std::shared_ptr<Trainer> trainer);
        private:
            std::shared_ptr<Layout> getLayout(std::string zoneName, std::shared_ptr<Trainer> trainer);
            
            std::shared_ptr<TextureLoader> textureLoader;
            std::shared_ptr<sf::View> view;
            std::unordered_map<std::string, std::shared_ptr<Tile>> tiles;
            std::unordered_map<std::string, std::shared_ptr<Block>> blocks;
    };
;}

#endif