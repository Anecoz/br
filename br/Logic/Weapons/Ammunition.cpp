#include "Ammunition.h"
#include "../../Utils/MathUtils.h"
#include "../Collision/CollisionHandler.h"
#include <glm\gtx\transform.hpp>

Ammunition::Ammunition(Texture* sprite, Texture* displaySprite, vec2 position, int damage, float layer, int uniqueId) : 
InventoryItem(sprite, displaySprite, position, layer, uniqueId) {
	
	this->damage = damage;
	this->box = CollisionBox(position.x, position.y, this->width, this->height, vec2(0));
}

void Ammunition::update(Level* level) {
	box.x = position.x;
	box.y = position.y;
	box.vel.x = velocity.x;
	box.vel.y = velocity.y;

	int tileX = (int)position.x;
	int tileY = (int)position.y;
	bool didCollide = false;
	CollisionBox tileRect;
	tileRect.w = 1;
	tileRect.h = 1;
	for (int x = -1; x <= 1; x++)
		for (int y = -1; y <= 1; y++) {
			if (level->getIsCollAt(tileX + x, tileY + y)) {
				tileRect.x = tileX + x;
				tileRect.y = tileY + y;
				float collTime = CollisionHandler::sweptAABBCollision(box, tileRect);
				// if collision
				if (collTime > 0.0f && collTime < 1.0f) {
					position += velocity*collTime;
					didCollide = true;
					this->dead = true;
					goto end_outer_loop;
				}
			}
		}
end_outer_loop:
	if (!didCollide) {
		position += velocity;
	}
	updateRotation();
}

void Ammunition::updateRotation() {
	double centerX = this->position.x + this->width / 2.0f;
	double centerY = this->position.y + this->height / 2.0f;

	vec3 center{ centerX, centerY, 0 };
	this->rotation = glm::translate(center) * glm::rotate(MathUtils::angle(this->velocity, vec2(0.0f, 1.0f)), vec3(0.0f, 0.0f, -1.0f)) * glm::translate(-center);
}