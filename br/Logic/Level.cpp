#include "Level.h"
#include "../Utils/LevelUtils.h"
#include "../Utils/GraphicsUtils.h"
#include "../Graphics/Shaders/ShaderHandler.h"
#include "../Graphics/Camera.h"
#include <glm/gtx/transform.hpp>
#include <vector>
#include <math.h>

#include <iostream>

using std::vector;

Level::Level(const string& fileName) {
	map = new Map();
	map->ParseFile(fileName);

	if (map->HasError()) {
		cerr << "Map creation error code: " << map->GetErrorCode() << ", error text: " << map->GetErrorText() << endl;
	}

	LevelUtils::printMapInfo(map);
	LevelUtils::setTileTexCoords(map);

	layer = map->GetTileLayer(0);
	tileSet = map->GetTileset(layer->GetTileTilesetIndex(0, 0));
	
	texAtlas = new Texture(tileSet->GetImage()->GetSource(), 1.0f);

	mesh = GraphicsUtils::createLevelQuad();
}

Level::~Level() {
	delete map;
	map = nullptr;
	delete texAtlas;
	texAtlas = nullptr;
	delete mesh;
	mesh = nullptr;
}

bool Level::getIsProp(const string& name, int x, int y) {
	MapTile tile1 = layer->GetTile(x, y);
	const Tile* tile = tileSet->GetTile(tile1.id);
	if (tile == nullptr)
		return false;
	else
		return tile->GetProperties().HasProperty(name);
}

bool Level::getIsCollAt(int x, int y) {
	return getIsProp("isCollision", x, y);
}

bool Level::getIsShadowCasterAt(int x, int y) {
	return getIsProp("isShadowCaster", x, y);
}

void Level::render(mat4& projMatrix) {
	ShaderHandler::levelShader->comeHere();

	// Uniforms
	ShaderHandler::levelShader->uploadMatrix(projMatrix, "projMatrix");
	ShaderHandler::levelShader->uploadVec(vec2(0), "playerPos");
	ShaderHandler::levelShader->uploadInt(map->GetWidth(), "worldWidth");
	ShaderHandler::levelShader->uploadInt(map->GetHeight(), "worldHeight");
	ShaderHandler::levelShader->uploadFloat(Camera::getWinSizeX(), "windowSizeX");
	ShaderHandler::levelShader->uploadFloat(Camera::getWinSizeY(), "windowSizeY");
	ShaderHandler::levelShader->uploadInt(1, "numLights");
	ShaderHandler::levelShader->uploadVec(Camera::getPosition(), "camPos");
	glActiveTexture(GL_TEXTURE0);
	texAtlas->bind();

	//vector<GLfloat> tex1, tex2;
	int size = ceil(Camera::getWinSizeX()) * ceil(Camera::getWinSizeY()) * 4;
	GLfloat* tex1 = new GLfloat[size];
	GLfloat* tex2 = new GLfloat[size];
	int numTiles = 0;
	int incrementer = 0;
	// Loop and get correct tiles to draw
	for (int y = (int)Camera::getPosition().y; y < Camera::getPosition().y + Camera::getWinSizeY(); y++) {
		for (int x = (int)Camera::getPosition().x; x < Camera::getPosition().x + Camera::getWinSizeX(); x++) {
			GLfloat* texCoords = layer->GetTile(x, y).texCoords;

			// Fill the VBOs
			tex1[incrementer] = texCoords[0]; tex2[incrementer] = texCoords[4]; incrementer++;
			tex1[incrementer] = texCoords[1]; tex2[incrementer] = texCoords[5]; incrementer++;
			tex1[incrementer] = texCoords[2]; tex2[incrementer] = texCoords[6]; incrementer++;
			tex1[incrementer] = texCoords[3]; tex2[incrementer] = texCoords[7]; incrementer++;

			numTiles++;
		}	
	}
	mesh->modifyTexBuffers(tex1, tex2, size);
	mesh->drawInstances(numTiles);
	delete[] tex1;
	delete[] tex2;

	texAtlas->unbind();
	ShaderHandler::levelShader->pissOff();
}