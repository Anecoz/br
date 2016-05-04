#include "Weapon.h"
#include "../../Input/MouseButtonInput.h"
#include "../../Input/KeyInput.h"
#include "../../Utils/ResourceHandler.h"
#include "../Level.h"

Weapon::Weapon(Texture* sprite, Texture* displaySprite, vec2 position, float layer, int uniqueId) : 
InventoryItem(sprite, displaySprite, position, layer, uniqueId) {

	forward = vec2(0);
}

Weapon::~Weapon() {
	if (shootTimer != nullptr) {
		delete shootTimer;
		shootTimer = nullptr;
	}
}

void Weapon::update(vec2& forward, vec2& position, mat4& rotation) {
	this->forward = forward;
	this->position = position;
	this->rotation = rotation;

	if (spawnBullet) {
		Level::ammunitionList.push_back(spawnAmmo());
		spawnBullet = false;
	}

	if (!isFiring) {
		if (shootTimer != nullptr)
			delete shootTimer; shootTimer = nullptr;
	}
}

void Weapon::checkFire() {
	if (isAutomatic) {
		if (MouseButtonInput::isMouseLeftDown())
			fire();
		else
			isFiring = false;
	}
	else {
		if (MouseButtonInput::isMouseButtonClicked(GLFW_MOUSE_BUTTON_1))
			fire();
		else
			isFiring = false;
	}

	if (KeyInput::isKeyClicked(GLFW_KEY_R)) {
		reload();
	}
}

void Weapon::fire() {
	if (magazine < 1) {
		// TODO: Notify of empty magazine
	}
	else {
		if (!isReloading && !isFiring) {
			isFiring = true;
			shootTimer = new Timer();
			shootTimer->create(0, (1000 / ((float)(roundsPerMinute / 60))),
				[this]() {
				if (magazine > 0) {
					spawnBullet = true;
					magazine--;
				}
			});
		}
	}
}

void Weapon::reload() {
	if (ammo > 0 && magazine < magazineSize && !isReloading) {
		isReloading = true;
		reloadTimer.create(0, (reloadTime * 1000), 
			[this]() {
			if (magazine != magazineSize) {
				if (ammo > 0) {
					ammo -= (magazineSize - magazine);
					magazine += (magazineSize + magazine);
					if (ammo <= 0) {
						magazine += ammo;
						ammo = 0;
					}
					if (magazine >= magazineSize) {
						magazine = magazineSize;
					}
				}
			}
			isReloading = false;
		});
	}
}

Bullet* Weapon::spawnAmmo() {
	vec2 bulletPos{
		this->position.x + this->width / 2.0f - ResourceHandler::bulletTexture->getWidthAfterScale() / 2.0f,
		this->position.y + this->height / 2.0f - ResourceHandler::bulletTexture->getHeightAfterScale() / 2.0f
	};
	vec2 bulletVel{ this->forward.x, this->forward.y };
	return new Bullet(bulletPos, bulletVel*0.1f, damage, 0);
}