#pragma once

#include <glm\glm.hpp>
#include "../../Graphics/Lowlevel/Texture.h"
#include "../Inventory/InventoryItem.h"
//#include "../Level.h"
#include "../Collision/CollisionBox.h"

using namespace glm;

class Level;

class Ammunition : public InventoryItem
{
public:
	Ammunition(Texture* sprite, Texture* displaySprite, vec2 position, int damage, float layer, int uniqueId);
	~Ammunition() = default;

	void update(Level* level);

	vec2& getVelocity() { return velocity; }
	int getDamage() { return damage; }
	int getUniqueId() { return uniqueId; }

	bool dead = false;

protected:
	vec2 velocity;	
	int damage = 0;
	CollisionBox box;

private:
	void updateRotation();
};

