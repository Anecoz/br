#pragma once

#include <glm\glm.hpp>

#include "..\Logic\Level.h"

using namespace glm;

// FRIENDLY REMINDER:
// Z: LAYER -1.1f IS CLOSEST TO CAMERA
// Z: LAYER < 0.9 IS FURTHEST AWAY
class Camera
{
public:
	Camera(int width, int height);
	~Camera() = default;

	void update(vec2& playerPos, float playerSpeed, Level* level);

	static float getWinSizeX() { return WIN_SIZE_X; }
	static float getWinSizeY() { return WIN_SIZE_Y; }
	static void setPosition(vec2& posIn) { position = posIn; }
	static vec2& getPosition() { return position; }
	mat4& getProjection();

private:
	mat4 projection;
	mat4 lookAtMat;
	static vec2 position;
	float invAr;
	static float WIN_SIZE_X;
	static float WIN_SIZE_Y;

	void updateCameraMovement(vec2& playerPos, float playerSpeed, Level* level);
};

