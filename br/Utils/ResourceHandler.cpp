#include "ResourceHandler.h"
#include "GraphicsUtils.h"

Texture* ResourceHandler::playerTexture;
Texture* ResourceHandler::assaultRifleTexture;
Texture* ResourceHandler::assaultRifleDisplayTexture;
Texture* ResourceHandler::bulletTexture;
Texture* ResourceHandler::sliderTexture;

IndexedVertexArray* ResourceHandler::playerQuad;
IndexedVertexArray* ResourceHandler::assaultRifleQuad;
IndexedVertexArray* ResourceHandler::bulletQuad;
IndexedVertexArray* ResourceHandler::sliderQuad;

ResourceHandler::ResourceHandler() {
}

ResourceHandler::~ResourceHandler() {

}

void ResourceHandler::init() {
	// Textures
	playerTexture = new Texture("Resource/characters/player.png", 1.0f);
	sliderTexture = new Texture("Resource/gui/slider.png", 1.0f);
	assaultRifleDisplayTexture = new Texture("Resource/weapons/assault_rifle_display.png", 1.0f);
	assaultRifleTexture = new Texture("Resource/weapons/assault_rifle.png", 1.0f);
	bulletTexture = new Texture("Resource/weapons/bullet.png", 0.2f);

	// Meshes
	playerQuad = GraphicsUtils::createModelQuad(playerTexture->getWidthAfterScale(), playerTexture->getHeightAfterScale(), -0.3f);
	sliderQuad = GraphicsUtils::createModelQuad(sliderTexture->getWidthAfterScale(), sliderTexture->getHeightAfterScale(), -0.3f);
	playerQuad = GraphicsUtils::createModelQuad(playerTexture->getWidthAfterScale(), playerTexture->getHeightAfterScale(), -0.3f);
	assaultRifleQuad = GraphicsUtils::createModelQuad(assaultRifleDisplayTexture->getWidthAfterScale(), assaultRifleDisplayTexture->getHeightAfterScale(), -0.2f);
	bulletQuad = GraphicsUtils::createModelQuad(bulletTexture->getWidthAfterScale(), bulletTexture->getHeightAfterScale(), -0.2f);
}

void ResourceHandler::cleanUp() {
	// Textures
	delete playerTexture; playerTexture = nullptr;
	delete sliderTexture; sliderTexture = nullptr;
	delete playerTexture; playerTexture = nullptr;
	delete assaultRifleDisplayTexture; assaultRifleDisplayTexture = nullptr;
	delete assaultRifleTexture; assaultRifleTexture = nullptr;
	delete bulletTexture; bulletTexture = nullptr;

	// Meshes
	delete sliderQuad; sliderQuad = nullptr;
	delete playerQuad; playerQuad = nullptr;
	delete assaultRifleQuad; assaultRifleQuad = nullptr;
	delete bulletQuad; bulletQuad = nullptr;
}
