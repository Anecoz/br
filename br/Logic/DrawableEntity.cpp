#include "DrawableEntity.h"
#include "../Utils/GraphicsUtils.h"

DrawableEntity::DrawableEntity(Texture* texture, vec2& initPos, float layer) {
	this->texture = texture;
	init(layer, initPos);
}

DrawableEntity::~DrawableEntity() {
	delete mesh; mesh = nullptr;
	delete texture; texture = nullptr;
}

void DrawableEntity::init(float layer, vec2& initPos) {
	this->width = texture->getWidthAfterScale();
	this->height = texture->getHeightAfterScale();
	this->scale = texture->getScale();
	this->position = initPos;

	// If not player, otherplayer, weapon or ammunition
	this->mesh = GraphicsUtils::createModelQuad(width, height, layer);
}