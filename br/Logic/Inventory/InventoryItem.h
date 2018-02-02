#pragma once

#include "../../Graphics/Lowlevel/Texture.h"
#include "../DrawableEntity.h"
#include <glm\glm.hpp>

using namespace glm;

class InventoryItem : public DrawableEntity
{
public:
	InventoryItem(Texture* sprite, Texture* displaySprite, vec2 position, float layer, int uniqueId);
	~InventoryItem() = default;

	int getUniqueId() { return uniqueId; }
	void setPosition(vec2& pos) { this->position = pos; }
	Texture* getTexture() { return this->texture; }
	Texture* getDisplayTexture() { return this->displayTexture; }
	IndexedVertexArray* getMesh() { return this->mesh; }
	void setRotation(const mat4& rotation) { this->rotation = rotation; }

protected:
	int uniqueId;
	Texture* displayTexture;
};

