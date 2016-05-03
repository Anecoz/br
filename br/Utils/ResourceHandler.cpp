#include "ResourceHandler.h"
#include "GraphicsUtils.h"

Texture* ResourceHandler::playerTexture;
IndexedVertexArray* ResourceHandler::playerQuad;

ResourceHandler::ResourceHandler() {

}

ResourceHandler::~ResourceHandler() {
	// Textures
	delete playerTexture; playerTexture = nullptr;
	
	// Meshes
	delete playerQuad; playerQuad = nullptr;
}

void ResourceHandler::init() {
	// Textures
	playerTexture = new Texture("Resource/characters/player.png", 1.0f);

	// Meshes
	playerQuad = GraphicsUtils::createModelQuad(playerTexture->getWidthAfterScale(), playerTexture->getHeightAfterScale(), -0.3f);
}
