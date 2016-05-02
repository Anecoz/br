#include "ShadowHandler.h"
#include "ShadowMap.h"

ShadowCasterTexture* ShadowHandler::shadowCasterTexture;

ShadowHandler::ShadowHandler() {

}

ShadowHandler::~ShadowHandler() {
	delete shadowCasterTexture; shadowCasterTexture = nullptr;
}

void ShadowHandler::init() {
	ShadowMap::init();
}

void ShadowHandler::calcShadowCaster(Level* level) {
	shadowCasterTexture = new ShadowCasterTexture();
	int width = level->getWidth();
	int height = level->getHeight();
	shadowCasterTexture->init(width, height);

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++) {
			shadowCasterTexture->addAt(x, y, (level->getIsShadowCasterAt(x, y)) ? 1 : 0);
		}

	shadowCasterTexture->convertToTexture();
}

void ShadowHandler::calcShadowMap(vector<vec2>& lightArr, mat4& proj, Level* level) {
	ShadowMap::calcShadowMap(lightArr, proj, level);
}

void ShadowHandler::bindShadowMap() {
	glBindTexture(GL_TEXTURE_2D, ShadowMap::shadowMapID);
}

void ShadowHandler::unbindShadowMap() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
