#pragma once
#include <string>
#include <glm\glm.hpp>
#include <vector>
#include <unordered_map>

#include "../Tmx/Tmx.h"
#include "../Graphics/Lowlevel/Texture.h"
#include "../Graphics/Lowlevel/IndexedVertexArray.h"
#include "../Graphics/Lowlevel/DynamicLevelVao.h"
#include "Inventory\InventoryItem.h"
//#include "Weapons\Ammunition.h"

class Ammunition;

using namespace std;
using namespace Tmx;
using namespace glm;

class Level
{
public:
	Level(const string& filename);
	~Level();

	static vector<Ammunition*> ammunitionList;
	static unordered_map<int, vector<InventoryItem*>> droppedItems;

	bool getIsShadowCasterAt(int x, int y);
	bool getIsCollAt(int x, int y);

	void addDroppedItem(InventoryItem* item);
	void removeItemById(vec2 position, int uniqueId);
	InventoryItem* getDroppedItemById(vec2 position, int uniqueId);
	InventoryItem* getClosestItemAt(vec2 playerPosition);

	int getWidth();
	int getHeight();

	void update();
	void render(mat4& projMatrix);
private:
	Map* map;
	const TileLayer* layer;
	const Tileset* tileSet;

	int texAtlasHeight;
	int texAtlasWidth;
	int tileWidth;
	int tileHeight;

	DynamicLevelVao* mesh;

	Texture* texAtlas;

	int hashPositionToTileIndex(vec2 position);
	bool getIsProp(const string& prop, int x, int y);
	void updateBullets();
};

