#include "LayoutLoader.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "game/Tile.hpp"
#include "util/Const.hpp"
#include <utility>

using namespace DGMon;

LayoutLoader::LayoutLoader() {
    std::unordered_map<std::string, Tile> tiles;
    Json::Reader reader;

    // TODO: Generalize to more texture sources
    std::ifstream outsideFile("data/tiles/outside.json");
    Json::Value tileData;
    reader.parse(outsideFile, tileData);

    for (auto key : tileData.getMemberNames()) {
        auto cur = tileData[key];
        Tile t {OUTSIDE, cur["texX"].asInt(), cur["texY"].asInt(), sf::Color::White};
        tiles.insert({key, t});
    }

    std::unordered_map<std::string, Block> blocks;

    std::ifstream blocksFile("data/blocks/blocks.json");
    Json::Value blockData;
    reader.parse(blocksFile, blockData);
    
    for (auto key : blockData.getMemberNames()) {
        auto cur = blockData[key];
        std::vector<Tile> blockTiles {};
        for (auto tile : cur["tiles"]) {
            if (tile.asString() == "") {
                blockTiles.push_back(TILE_NONE);
            } else {
                blockTiles.push_back(tiles.at(tile.asString()));
            }
        }
        std::vector<int> heights {};
        for (auto height : cur["heights"]) {
            heights.push_back(height.asInt());
        }
        blocks.insert({key, Block (blockTiles, heights)});
    }

    // Load textures
    sf::Texture outdoorTexture;
    if (!outdoorTexture.loadFromFile("assets/tilesets/outside.png")) {
        std::cerr << "Failed to load outside texture\n";
    }

    // Initialize player
    Trainer trainer(1280 / 2, 960 / 2);
    trainer.refresh();

    std::ifstream zonesFile("data/zones/zones.json");
    Json::Value zonesData;
    reader.parse(zonesFile, zonesData);

    for (auto key : zonesData.getMemberNames()) {
        auto cur = zonesData[key];
        std::vector<Block> layer0Blocks {};
        for (auto block : cur["layer0"]) {
            layer0Blocks.push_back(blocks.at(block.asString()));
        }
        std::vector<Block> layer1Blocks {};
        for (auto block : cur["layer1"]) {
            layer1Blocks.push_back(blocks.at(block.asString()));
        }
        Zone z1(layer0Blocks, outdoorTexture, trainer);
        z1.load();
        Zone z2(layer1Blocks, outdoorTexture, trainer);
        z2.load();
        zonesLayer0.insert({key, z1});
        zonesLayer1.insert({key, z2});
    }
}

LayoutLoader::~LayoutLoader() {
    
}

std::pair<Zone, Zone> LayoutLoader::getZone(std::string zoneName) {
    return std::make_pair(zonesLayer0.at(zoneName), zonesLayer1.at(zoneName));
}