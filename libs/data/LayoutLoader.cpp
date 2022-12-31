#include "LayoutLoader.hpp"
#include "game/ZoneLayer.hpp"
#include "state/StateTransition.hpp"
#include "util/Direction.hpp"
#include <memory>

using namespace DGMon;

LayoutLoader::LayoutLoader() {
    const std::shared_ptr<Tile> TILE_NONE_PTR = std::make_shared<Tile>(OUTSIDE, 0, 0, sf::Color(0, 0, 0, 0));
    std::unordered_map<std::string, std::shared_ptr<Tile>> tiles;
    Json::Reader reader;

    // TODO: Generalize to more texture sources
    std::ifstream outsideFile("data/tiles/outside.json");
    Json::Value tileData;
    reader.parse(outsideFile, tileData);

    for (auto key : tileData.getMemberNames()) {
        auto cur = tileData[key];
        auto t = std::make_shared<Tile>(OUTSIDE, cur["texX"].asInt(), cur["texY"].asInt(), sf::Color::White);
        tiles.insert({key, t});
    }
    
    std::unordered_map<std::string, std::shared_ptr<Block>> blocks;

    std::ifstream blocksFile("data/blocks/blocks.json");
    Json::Value blockData;
    reader.parse(blocksFile, blockData);
    
    for (auto key : blockData.getMemberNames()) {
        auto cur = blockData[key];
        std::vector<std::shared_ptr<Tile>> blockTiles;
        for (auto tile : cur["tiles"]) {
            if (tile.asString() == "") {
                blockTiles.push_back(TILE_NONE_PTR);
            } else {
                blockTiles.push_back(tiles.at(tile.asString()));
            }
        }
        std::vector<int> heights {};
        for (auto height : cur["heights"]) {
            heights.push_back(height.asInt());
        }
        auto name = cur["name"].asString();
        blocks[key] = std::move(std::make_shared<Block>(name, blockTiles, heights));
    }

    // Load textures
    sf::Texture outdoorTexture;
    if (!outdoorTexture.loadFromFile("assets/tilesets/outside.png")) {
        std::cerr << "Failed to load outside texture\n";
    }

    std::ifstream layoutsFile("data/layouts/layouts.json");
    Json::Value layoutsData;
    reader.parse(layoutsFile, layoutsData);

    for (auto key : layoutsData.getMemberNames()) {
        auto cur = layoutsData[key];
        
        int widthBlocks = cur["width"].asInt();
        int heightBlocks = cur["height"].asInt();

        std::vector<std::shared_ptr<ZoneLayer>> backgroundLayers {};
        std::vector<std::shared_ptr<ZoneLayer>> foregroundLayers {};

        for (auto layer : cur["layers"]) {
            std::vector<std::shared_ptr<Block>> layerBlocks;

            for (auto block : layer["blocks"]) {
                layerBlocks.push_back(blocks.at(block.asString()));
            }

            auto zoneLayer = std::make_shared<ZoneLayer>(widthBlocks, heightBlocks, layerBlocks, outdoorTexture);

            if (layer["type"].asString() == "background") {
                backgroundLayers.push_back(zoneLayer);
            } else if (layer["type"].asString() == "foreground") {
                foregroundLayers.push_back(zoneLayer);
            }
        }

        std::vector<std::shared_ptr<Connection>> connections;
        for (auto connection : cur["connections"]) {
            Direction dir = NONE_DIRECTION;
            std::string dirName = connection["direction"].asString();

            if (dirName == "UP") {
                dir = UP_DIRECTION;
            } else if (dirName == "DOWN") {
                dir = DOWN_DIRECTION;
            } else if (dirName == "LEFT") {
                dir = LEFT_DIRECTION;
            } else if (dirName == "RIGHT") {
                dir = RIGHT_DIRECTION;
            }

            StateTransition transition;
            transition.type = StateTransitionType::CONNECT;
            transition.attribute = cur["target"].asString();

            connections.push_back(std::make_shared<Connection>(transition, cur["x"].asInt(), cur["y"].asInt(), dir));
        }

        std::shared_ptr<Layout> layout = std::make_shared<Layout>(key, widthBlocks, heightBlocks, backgroundLayers, foregroundLayers, connections);
        layouts.insert({key, layout});
    }
}

LayoutLoader::~LayoutLoader() {
    
}

std::shared_ptr<Layout> LayoutLoader::getLayout(std::string zoneName) {
    return layouts.at(zoneName);
}
