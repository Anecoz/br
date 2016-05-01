#include "LevelUtils.h"

void LevelUtils::printMapInfo(Map* map) {
	cout << "=========================================" << endl;
	cout << " MAP INFO " << endl;
	cout << "=========================================" << endl;
	cout << "Map orientation: " << map->GetOrientation() << endl;
	cout << "Map version: " << map->GetVersion() << endl;
	cout << "Map render order: " << map->GetRenderOrder() << endl;
	cout << "Map width: " << map->GetWidth() << endl;
	cout << "Map height: " << map->GetHeight() << endl;
	cout << "Map tile width: " << map->GetTileWidth() << endl;
	cout << "Map tile height: " << map->GetTileHeight() << endl;
	cout << "Map num tilesets: " << map->GetNumTilesets() << endl;
	cout << "=========================================" << endl;
	cout << " MAP INFO END " << endl;
	cout << "=========================================" << endl;
}

void LevelUtils::setTileTexCoords(Map* map) {
	const TileLayer* layer = map->GetTileLayer(0);
	const Tileset* tileset = map->GetTileset(layer->GetTileTilesetIndex(0, 0));
	const Image* tileImage = tileset->GetImage();
	unsigned imWidth = tileImage->GetWidth();
	unsigned imHeight = tileImage->GetHeight();
	unsigned tileHeight = map->GetTileset(layer->GetTileTilesetIndex(0, 0))->GetTileHeight();
	unsigned tileWidth = map->GetTileset(layer->GetTileTilesetIndex(0, 0))->GetTileWidth();
	for (int y = 0; y < layer->GetHeight(); y++)
		for (int x = 0; x < layer->GetWidth(); x++) {
			layer->GetTile(x, y).setTexCoords(imWidth, imHeight, tileWidth, tileHeight);
		}
}