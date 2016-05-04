#include "ResourceHandler.h"
#include "GraphicsUtils.h"

Texture* ResourceHandler::playerTexture;
IndexedVertexArray* ResourceHandler::playerQuad;
Texture* ResourceHandler::sliderTexture;
IndexedVertexArray* ResourceHandler::sliderQuad;

ResourceHandler::ResourceHandler() {
}

ResourceHandler::~ResourceHandler() {	
}

void ResourceHandler::init() {
	// Textures
	playerTexture = new Texture("Resource/characters/player.png", 1.0f);
	sliderTexture = new Texture("Resource/gui/slider.png", 1.0f);

	// Meshes
	playerQuad = GraphicsUtils::createModelQuad(playerTexture->getWidthAfterScale(), playerTexture->getHeightAfterScale(), -0.3f);
	sliderQuad = GraphicsUtils::createModelQuad(sliderTexture->getWidthAfterScale(), sliderTexture->getHeightAfterScale(), -0.3f);
}

void ResourceHandler::cleanUp() {
	// Textures
	delete playerTexture; playerTexture = nullptr;
	delete sliderTexture; sliderTexture = nullptr;

	// Meshes
	delete playerQuad; playerQuad = nullptr;
	delete sliderQuad; sliderQuad = nullptr;
}
