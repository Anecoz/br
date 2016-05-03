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

			// Fill the VBOs
			/*tex1[incrementer] = texCoords[0]; tex2[incrementer] = texCoords[4]; incrementer++;
			tex1[incrementer] = texCoords[1]; tex2[incrementer] = texCoords[5]; incrementer++;
			tex1[incrementer] = texCoords[2]; tex2[incrementer] = texCoords[6]; incrementer++;
			tex1[incrementer] = texCoords[3]; tex2[incrementer] = texCoords[7]; incrementer++;*/

			/*tex1.push_back(texCoords[0]);
			tex1.push_back(texCoords[1]);
			tex1.push_back(texCoords[2]);
			tex1.push_back(texCoords[3]);
			tex2.push_back(texCoords[4]);
			tex2.push_back(texCoords[5]);
			tex2.push_back(texCoords[6]);
			tex2.push_back(texCoords[7]);*/

			trans.push_back(x);
			trans.push_back(y);

			ids.push_back(layer->GetTile(x, y).id);

			numTiles++;
		}	
	}
	//mesh->modifyTexBuffers(&tex1[0], &tex2[0], tex1.size());
	mesh->modifyTranslationBuffer(&trans[0], trans.size());
	mesh->modifyIdBuffer(&ids[0], ids.size());
	mesh->drawInstances(numTiles);
	//delete[] tex1;
	//delete[] tex2;

	texAtlas->unbind();
	ShadowHandler::unbindShadowMap();
	ShaderHandler::levelShader->pissOff();

	glActiveTexture(GL_TEXTURE0);
	/*GLubyte* back = new GLubyte[25*25];
	ShadowHandler::bindShadowMap();
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, back);

	cout << "back at 5, 6: " << static_cast<unsigned>(back[6 * 25 + 5]) << endl;

	delete[] back;*/
}