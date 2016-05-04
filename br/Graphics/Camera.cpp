#include "Camera.h"
#include <glm/gtx/transform.hpp>

vec2 Camera::position{ 0.0f };
float Camera::WIN_SIZE_X = 0.0f;
float Camera::WIN_SIZE_Y = 0.0f;
mat4 Camera::projection;
mat4 Camera::lookAtMat;

Camera::Camera(int width, int height) {
	invAr = (float)height / (float)width;
	Camera::WIN_SIZE_X = 20.0f;
	Camera::WIN_SIZE_Y = invAr * WIN_SIZE_X;

	lookAtMat = lookAt(vec3(0.0f, 0.0f, -0.1f), vec3(0.0f), vec3(0.0f, -1.0f, 0.0f));
	projection = ortho(position.x, position.x + WIN_SIZE_X, -(position.y + WIN_SIZE_Y), -position.y, -1.0f, 1.0f);
}

mat4& Camera::getProjection() {
	projection = ortho(position.x, position.x + WIN_SIZE_X, -(position.y + WIN_SIZE_Y), -position.y, -1.0f, 1.0f)*lookAtMat;
	return projection;
}

void Camera::update(vec2& playerPos, float playerSpeed, Level* level) {
	updateCameraMovement(playerPos, playerSpeed, level);
}

void Camera::updateCameraMovement(vec2& playerPos, float playerSpeed, Level* level) {
	vec2 topLeft{ position.x + (WIN_SIZE_X / 3), position.y + (WIN_SIZE_Y / 3) };
	vec2 topRight{ position.x + (WIN_SIZE_X * 2) / 3, position.y + (WIN_SIZE_Y / 3) };
	vec2 bottomRight{ position.x + ((WIN_SIZE_X * 2) / 3), position.y + ((WIN_SIZE_Y * 2) / 3) };
	vec2 bottomLeft{ position.x + (WIN_SIZE_X / 3), position.y + ((WIN_SIZE_Y * 2) / 3) };
	vec2 tempPos{ position.x, position.y };

	// Side Check
	if (playerPos.y <= topLeft.y && playerPos.x >= topLeft.x && playerPos.x <= topRight.x) {
		position.y += -playerSpeed;
	}
	if (playerPos.x >= topRight.x && playerPos.y >= topRight.y && playerPos.y <= bottomRight.y) {
		position.x += playerSpeed;
	}
	if (playerPos.x >= bottomLeft.x && playerPos.x <= bottomRight.x && playerPos.y >= bottomRight.y) {
		position.y += playerSpeed;
	}
	if (playerPos.x <= topLeft.x && playerPos.y >= topLeft.y && playerPos.y <= bottomLeft.y) {
		position.x += -playerSpeed;
	}

	// Diagonal Check
	if (playerPos.x <= topLeft.x && playerPos.y <= topLeft.y) {
		position.y += -playerSpeed;
		position.x += -playerSpeed;
	}
	if (playerPos.x >= topRight.x && playerPos.y <= topRight.y) {
		position.y += -playerSpeed;
		position.x += playerSpeed;
	}
	if (playerPos.x >= bottomRight.x && playerPos.y >= bottomRight.y) {
		position.y += playerSpeed;
		position.x += playerSpeed;
	}
	if (playerPos.x <= bottomLeft.x && playerPos.y >= bottomLeft.y) {
		position.y += playerSpeed;
		position.x += -playerSpeed;
	}

	// Check camera map bounds
	if (position.x < 0) {
		position.x = tempPos.x;
	}
	if (position.y < 0) {
		position.y = tempPos.y;
	}
	if ((position.x + WIN_SIZE_X) > level->getWidth()) {
		position.x = tempPos.x;
	}
	if ((position.y + WIN_SIZE_Y) > level->getHeight()) {
		position.y = tempPos.y;
	}
}