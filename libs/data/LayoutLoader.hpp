#ifndef LAYOUT_LOADER_H
#define LAYOUT_LOADER_H

#include "game/Game.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <json/json.h>
#include <fstream>
#include <SFML/Graphics.hpp>

namespace DGMon {
    class LayoutLoader {
        public:
            LayoutLoader();
            ~LayoutLoader();
            std::pair<Zone, Zone> getZone(std::string zoneName);
        private:
            std::unordered_map<std::string, Tile> tiles;
            std::unordered_map<std::string, Block> blocks;
            std::unordered_map<std::string, Zone> zones;
            std::unordered_map<std::string, Zone> zones3d;
    };
;}

#endif