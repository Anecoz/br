#include "CollisionBox.h"

CollisionBox::CollisionBox() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	vel = vec2(0);
}

CollisionBox::CollisionBox(float x, float y, float w, float h, vec2& vel) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->vel = vel;
}