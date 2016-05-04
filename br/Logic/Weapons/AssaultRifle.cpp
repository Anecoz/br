#include "AssaultRifle.h"
#include "../../Utils/ResourceHandler.h"

AssaultRifle::AssaultRifle(vec2 position, float layer, int currentMagazine, int ammo, int roundsPerMinute, int uniqueId) :
Weapon(ResourceHandler::assaultRifleTexture, ResourceHandler::assaultRifleDisplayTexture, position, layer, uniqueId) {

	this->reloadTime = reloadTime;
	this->magazineSize = MAG_SIZE;
	this->damage = DAMAGE;
	this->magazine = currentMagazine;
	this->ammo = ammo;
	this->roundsPerMinute = roundsPerMinute;
	this->position = position;
	this->isAutomatic = true;
	this->isReloading = false;
	this->isFiring = false;
	this->spawnBullet = false;

	this->mesh = ResourceHandler::assaultRifleQuad;
}

AssaultRifle::~AssaultRifle() {
	Weapon::~Weapon();
}
