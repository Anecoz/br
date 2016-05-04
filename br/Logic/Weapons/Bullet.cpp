#include "Bullet.h"
#include "../../Utils/ResourceHandler.h"

Bullet::Bullet(vec2 position, vec2 velocity, int damage, int uniqueId) :
Ammunition(ResourceHandler::bulletTexture, ResourceHandler::bulletTexture, position, damage, -0.8f, uniqueId) {
	this->velocity = velocity;
	this->mesh = ResourceHandler::bulletQuad;
}