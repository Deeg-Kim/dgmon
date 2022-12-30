#include "LayoutLoader.hpp"
#include "game/Tile.hpp"
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

    std::ifstream zonesFile("data/zones/zones.json");
    Json::Value zonesData;
    reader.parse(zonesFile, zonesData);

    for (auto key : zonesData.getMemberNames()) {
        auto cur = zonesData[key];
        std::vector<std::shared_ptr<Block>> layer0Blocks;
        for (auto block : cur["layer0"]) {
            layer0Blocks.push_back(blocks.at(block.asString()));
        }
        std::vector<std::shared_ptr<Block>> layer1Blocks;
        for (auto block : cur["layer1"]) {
            layer1Blocks.push_back(blocks.at(block.asString()));
        }
        std::vector<std::shared_ptr<Block>> layer2Blocks;
        for (auto block : cur["layer2"]) {
            layer2Blocks.push_back(blocks.at(block.asString()));
        }
        auto z0 = std::shared_ptr<Zone>(new Zone(layer0Blocks, outdoorTexture));
        auto z1 = std::shared_ptr<Zone>(new Zone(layer1Blocks, outdoorTexture));
        auto z2 = std::shared_ptr<Zone>(new Zone(layer2Blocks, outdoorTexture));
        std::shared_ptr<Layout> layout = std::make_shared<Layout>(z0, z1, z2);
        layouts.insert({key, layout});
    }
}

LayoutLoader::~LayoutLoader() {
    
}

std::shared_ptr<Layout> LayoutLoader::getLayout(std::string zoneName) {
    return layouts.at(zoneName);
}
