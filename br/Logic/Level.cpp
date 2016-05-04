#include "Level.h"
#include "../Utils/LevelUtils.h"
#include "../Utils/GraphicsUtils.h"
#include "../Graphics/Shaders/ShaderHandler.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Shadows/ShadowHandler.h"
#include "../Graphics/Lighting/LightHandler.h"
#include <glm/gtx/transform.hpp>
#include <vector>
#include <math.h>
#include <algorithm>

#include <iostream>

vector<Ammunition*> Level::ammunitionList;

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

	const Tileset* tileset = map->GetTileset(layer->GetTileTilesetIndex(0, 0));
	const Image* tileImage = tileset->GetImage();
	texAtlasWidth = tileImage->GetWidth();
	texAtlasHeight = tileImage->GetHeight();
	tileHeight = map->GetTileset(layer->GetTileTilesetIndex(0, 0))->GetTileHeight();
	tileWidth = map->GetTileset(layer->GetTileTilesetIndex(0, 0))->GetTileWidth();
}

Level::~Level() {
	delete map;
	map = nullptr;
	delete texAtlas;
	texAtlas = nullptr;
	delete mesh;
	mesh = nullptr;
}

void Level::update() {
	updateBullets();
}

void Level::updateBullets() {
	auto it = ammunitionList.begin();
	while (it != ammunitionList.end()) {
		if ((*it)->dead) {
			delete (*it);
			it = ammunitionList.erase(it);
		}
		else {
			(*it)->update(this);
			++it;
		}			
	}
	/*ammunitionList.erase(remove_if(ammunitionList.begin(), ammunitionList.end(),
		[](Ammunition* ammo) {return ammo->dead; }), ammunitionList.end());*/
}

int Level::getWidth() {
	return map->GetWidth();
}

int Level::getHeight() {
	return map->GetHeight();
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
	ShaderHandler::levelShader->uploadVec(vec2(10), "playerPos");
	ShaderHandler::levelShader->uploadFloat(1280.0, "screenWidth");
	ShaderHandler::levelShader->uploadFloat(720.0, "screenHeight");
	ShaderHandler::levelShader->uploadFloat(Camera::getWinSizeX(), "windowSizeX");
	ShaderHandler::levelShader->uploadFloat(Camera::getWinSizeY(), "windowSizeY");
	ShaderHandler::levelShader->uploadInt(1, "numLights");
	ShaderHandler::levelShader->uploadVec(LightHandler::lightList.at(0), "lightPos");
	ShaderHandler::levelShader->uploadVec(Camera::getPosition(), "camPos");
	ShaderHandler::levelShader->uploadVec(vec2(texAtlasWidth, texAtlasHeight), "texAtlasDimensions");
	ShaderHandler::levelShader->uploadVec(vec2(tileWidth, tileHeight), "tileDimensions");
	glActiveTexture(GL_TEXTURE0);
	texAtlas->bind();
	glActiveTexture(GL_TEXTURE1);
	ShadowHandler::bindShadowMap();

	//int size = Camera::getWinSizeX() * Camera::getWinSizeY() * 4;
	//GLfloat* tex1 = new GLfloat[size];
	//GLfloat* tex2 = new GLfloat[size];
	//vector<GLfloat> tex1;
	//vector<GLfloat> tex2;
	vector<GLfloat> trans;
	vector<GLfloat> ids;
	int numTiles = 0;
	//int incrementer = 0;
	// Loop and get correct tiles to draw
	vec2 c = Camera::getPosition();
	float fcx = floor(c.x);
	float fcy = floor(c.y);
	int maxX = this->getWidth() - 1;
	int maxY = this->getHeight() - 1;
	for (int y = fcy - 1; y < fcy + Camera::getWinSizeY() + 1; y++) {
		for (int x = fcx - 1; x < fcx + Camera::getWinSizeX() + 1; x++) {
			if (x < 0 || x > maxX || y < 0 || y > maxY)
				continue;
			GLfloat* texCoords = &(layer->GetTile(x, y).texCoords)[0];

			trans.push_back(x);
			trans.push_back(y);

			ids.push_back(layer->GetTile(x, y).id);

			numTiles++;
		}	
	}
	mesh->modifyTranslationBuffer(&trans[0], trans.size());
	mesh->modifyIdBuffer(&ids[0], ids.size());
	mesh->drawInstances(numTiles);
	//delete[] tex2;

	texAtlas->unbind();
	ShadowHandler::unbindShadowMap();
	ShaderHandler::levelShader->pissOff();
	glActiveTexture(GL_TEXTURE0);

	for (Ammunition* ammo : ammunitionList) {
		ammo->render(projMatrix);
	}
}