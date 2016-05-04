#include "ResourceHandler.h"
#include "GraphicsUtils.h"

Texture* ResourceHandler::playerTexture;
Texture* ResourceHandler::assaultRifleTexture;
Texture* ResourceHandler::assaultRifleDisplayTexture;
Texture* ResourceHandler::bulletTexture;

IndexedVertexArray* ResourceHandler::playerQuad;
IndexedVertexArray* ResourceHandler::assaultRifleQuad;
IndexedVertexArray* ResourceHandler::bulletQuad;

ResourceHandler::ResourceHandler() {

}

ResourceHandler::~ResourceHandler() {
	// Textures
	delete playerTexture; playerTexture = nullptr;
	delete assaultRifleDisplayTexture; assaultRifleDisplayTexture = nullptr;
	delete assaultRifleTexture; assaultRifleTexture = nullptr;
	delete bulletTexture; bulletTexture = nullptr;
	
	// Meshes
	delete playerQuad; playerQuad = nullptr;
	delete assaultRifleQuad; assaultRifleQuad = nullptr;
	delete bulletQuad; bulletQuad = nullptr;
}

void ResourceHandler::init() {
	// Textures
	playerTexture = new Texture("Resource/characters/player.png", 1.0f);
	assaultRifleDisplayTexture = new Texture("Resource/weapons/assault_rifle_display.png", 1.0f);
	assaultRifleTexture = new Texture("Resource/weapons/assault_rifle.png", 1.0f);
	bulletTexture = new Texture("Resource/weapons/bullet.png", 0.2f);

	// Meshes
	playerQuad = GraphicsUtils::createModelQuad(playerTexture->getWidthAfterScale(), playerTexture->getHeightAfterScale(), -0.3f);
	assaultRifleQuad = GraphicsUtils::createModelQuad(assaultRifleDisplayTexture->getWidthAfterScale(), assaultRifleDisplayTexture->getHeightAfterScale(), -0.2f);
	bulletQuad = GraphicsUtils::createModelQuad(bulletTexture->getWidthAfterScale(), bulletTexture->getHeightAfterScale(), -0.2f);
}
