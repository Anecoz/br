#pragma once
#include <string>
#include <glm\glm.hpp>

#include "../Tmx/Tmx.h"
#include "../Graphics/Lowlevel/Texture.h"
#include "../Graphics/Lowlevel/IndexedVertexArray.h"

using namespace std;
using namespace Tmx;
using namespace glm;

class Level
{
public:
	Level(const string& filename);
	~Level();

	bool getIsShadowCasterAt(int x, int y);
	bool getIsCollAt(int x, int y);

	void render(mat4& projMatrix);
private:
	Map* map;
	const TileLayer* layer;
	const Tileset* tileSet;

	IndexedVertexArray* mesh;

	Texture* texAtlas;

	bool getIsProp(const string& prop, int x, int y);
};

