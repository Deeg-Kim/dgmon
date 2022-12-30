#ifndef LAYOUT_LOADER_H
#define LAYOUT_LOADER_H

#include "game/Game.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <memory>
#include <json/json.h>
#include <SFML/Graphics.hpp>

namespace DGMon {
    class LayoutLoader {
        public:
            LayoutLoader();
            ~LayoutLoader();
            std::shared_ptr<Layout> getLayout(std::string zoneName);
        private:
            std::unordered_map<std::string, std::shared_ptr<Layout>> layouts;
    };
;}

#endif