#pragma once

#include "../../Graphics/Lowlevel/Texture.h"
#include "../Inventory/InventoryItem.h"
#include "../../Utils/Timer.h"
#include "Bullet.h"
#include <glm\glm.hpp>

using namespace glm;

class Weapon : public InventoryItem
{
public:
	Weapon(Texture* sprite, Texture* displaySprite, vec2 position, float layer, int uniqueId);
	~Weapon();

	void update(vec2& forward, vec2& position, mat4& rotation);
	void checkFire();

	int getMagazine() { return magazine; }
	int getAmmo() { return ammo; }
	int getDamage() { return damage; }

protected:
	float reloadTime;
	int magazineSize;
	int magazine;
	int ammo;
	int roundsPerMinute;
	int damage;
	bool isReloading = false;
	bool isFiring = false;
	bool isAutomatic;
	vec2 forward;
	Timer reloadTimer;
	Timer* shootTimer;
	bool spawnBullet;

	void fire();
	void reload();

private:
	Bullet* spawnAmmo();
};

