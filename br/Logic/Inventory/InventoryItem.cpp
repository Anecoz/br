#include "InventoryItem.h"

InventoryItem::InventoryItem(Texture* sprite, Texture* displayTexture, vec2 position, float layer, int uniqueId) :
DrawableEntity(sprite, position, layer) {
	this->displayTexture = displayTexture;
	this->uniqueId = uniqueId;
}
