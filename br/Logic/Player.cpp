#include "Player.h"
#include "../Input/KeyInput.h"
#include "../Input/MousePosInput.h"
#include "Collision\CollisionHandler.h"
#include "../Utils/MathUtils.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtx\vector_angle.hpp>

const float Player::SPEED = 0.06f;

Player::Player() : DrawableEntity(ResourceHandler::playerTexture, vec2(10), -0.3f) {
	this->mesh = ResourceHandler::playerQuad;
	rifle = new AssaultRifle(position, -0.2f, AssaultRifle::MAG_SIZE, 40, 800, 10);
	inventory = new Inventory();
	inventory->add(rifle);
	inventory->setEquipedWeapon(rifle);
}

Player::~Player() {

}

void Player::update(Level* level, mat4& proj) {
	updateMovement(level);
	checkRunningStatus();
	inventory->update(level);

	if (!inventory->isDragging() && inventory->getEquipedWeapon() != nullptr) {
		rifle->checkFire();
	}

	updateForward(proj);
	rifle->update(this->forward, this->position, this->rotation);
}

void Player::updateMovement(Level* level) {
	vec2 tmp = this->getPosition();
	if (KeyInput::isKeyDown(GLFW_KEY_W)) {
		position.y -= SPEED;
		if (CollisionHandler::checkPlayerCollision(this, level))
			position.y = tmp.y;
	}
	if (KeyInput::isKeyDown(GLFW_KEY_S)) {
		position.y += SPEED;
		if (CollisionHandler::checkPlayerCollision(this, level))
			position.y = tmp.y;
	}
	if (KeyInput::isKeyDown(GLFW_KEY_A)) {
		position.x -= SPEED;
		if (CollisionHandler::checkPlayerCollision(this, level))
			position.x = tmp.x;
	}
	if (KeyInput::isKeyDown(GLFW_KEY_D)) {
		position.x += SPEED;
		if (CollisionHandler::checkPlayerCollision(this, level))
			position.x = tmp.x;
	}
}

void Player::render(mat4& proj) {
	DrawableEntity::render(proj);
	rifle->render(proj);
	inventory->render(proj);
}

bool Player::isDead() {
	return health <= 0;
}

void Player::checkRunningStatus() {
	if (anyRunningKeysDown()) {
		if (!running) {
			running = true;
			// TODO ANIMATION START
		}
	}

	if (noRunningKeysDown()) {
		running = false;
		// TODO ANIMATION STOP
	}
}

bool Player::anyRunningKeysDown() {
	return (KeyInput::isKeyDown(GLFW_KEY_A) || KeyInput::isKeyDown(GLFW_KEY_S) ||
		KeyInput::isKeyDown(GLFW_KEY_D) || KeyInput::isKeyDown(GLFW_KEY_W));
}

bool Player::noRunningKeysDown() {
	return (!KeyInput::isKeyDown(GLFW_KEY_A) && !KeyInput::isKeyDown(GLFW_KEY_S) &&
		!KeyInput::isKeyDown(GLFW_KEY_D) && !KeyInput::isKeyDown(GLFW_KEY_W));
}

void Player::updateForward(mat4& proj) {
	double mouseX = MousePosInput::getPosition().x;
	double mouseY = MousePosInput::getPosition().y;
	double centerX = this->position.x + this->width / 2.0f;
	double centerY = this->position.y + this->height / 2.0f;
	vec2 mouse{ mouseX, mouseY };
	MathUtils::screenSpaceToWorld(mouse, 1280, 720, proj);
	this->forward.x = mouse.x - centerX;
	this->forward.y = mouse.y - centerY;
	normalize(this->forward);
	// Rotation matrix
	vec3 center{ centerX, centerY, 0 };
	this->rotation = glm::translate(center) * glm::rotate(MathUtils::angle(this->forward, vec2(0.0f, 1.0f)), vec3(0.0f, 0.0f, -1.0f)) * glm::translate(-center);
}