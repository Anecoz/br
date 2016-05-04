#pragma once

#include "Weapon.h"
#include "../../Graphics/Lowlevel/Texture.h"
#include <glm\glm.hpp>

using namespace glm;


class AssaultRifle :
	public Weapon
{
public:
	AssaultRifle(vec2 position, float layer, int currentMagazine, int ammo, int roundsPerMinute, int uniqueId);
	~AssaultRifle();

	static const int MAG_SIZE = 40;
private:
	const int DAMAGE = 26;
};

