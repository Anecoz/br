#include "Level.h"
#include "../Utils/LevelUtils.h"
#include "../Utils/GraphicsUtils.h"
#include "../Graphics/Shaders/ShaderHandler.h"
#include "../Graphics/Camera.h"
#include <glm/gtx/transform.hpp>
#include <vector>

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

	vec4 texCoordVec1;
	vec4 texCoordVec2;
	mat4 translationMatrix;
	vector<GLfloat> tex1, tex2;
	int counter = 0;
	// Loop and get correct tiles to draw
	for (int y = (int)Camera::getPosition().y; y < Camera::getPosition().y + Camera::getWinSizeY(); y++) {
		for (int x = (int)Camera::getPosition().x; x < Camera::getPosition().x + Camera::getWinSizeX(); x++) {
			GLfloat* texCoords = layer->GetTile(x, y).texCoords;

			// Fill the VBOs
			tex1.push_back(texCoords[0]);
			tex1.push_back(texCoords[1]);
			tex1.push_back(texCoords[2]);
			tex1.push_back(texCoords[3]);
			tex2.push_back(texCoords[4]);
			tex2.push_back(texCoords[5]);
			tex2.push_back(texCoords[6]);
			tex2.push_back(texCoords[7]);

			counter++;

			/*texCoordVec1.x = texCoords[0];
			texCoordVec1.y = texCoords[1];
			texCoordVec1.z = texCoords[2];
			texCoordVec1.w = texCoords[3];
			texCoordVec2.x = texCoords[4];
			texCoordVec2.y = texCoords[5];
			texCoordVec2.z = texCoords[6];
			texCoordVec2.w = texCoords[7];
			ShaderHandler::levelShader->uploadVec(texCoordVec1, "texCoords1");
			ShaderHandler::levelShader->uploadVec(texCoordVec2, "texCoords2");

			translationMatrix = glm::translate(mat4(1.0f), vec3(x, y, 0));
			ShaderHandler::levelShader->uploadMatrix(translationMatrix, "translationMatrix");*/			
		}	
	}
	mesh->modifyTexBuffers(tex1, tex2, tex1.size());
	mesh->drawInstances(counter);

	texAtlas->unbind();
	ShaderHandler::levelShader->pissOff();
}