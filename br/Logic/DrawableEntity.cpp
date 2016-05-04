#include "DrawableEntity.h"
#include "../Utils/GraphicsUtils.h"
#include "../Graphics/Shaders/ShaderHandler.h"
#include "../Graphics/Shadows/ShadowHandler.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Lighting/LightHandler.h"
#include "../Graphics/GUI/Slider.h"
#include "../Graphics/GUI/CheckBox.h"
#include "Player.h"
#include "Weapons\Weapon.h"
#include "Inventory\InventoryItem.h"

#include <typeinfo>
#include <glm\gtx\transform.hpp>

DrawableEntity::DrawableEntity(Texture* texture, vec2& initPos, float layer) {
	this->texture = texture;
	init(layer, initPos);
}

DrawableEntity::~DrawableEntity() {
	/*if (typeid(this) != typeid(Player) && 
		typeid(this) != typeid(Slider) &&
		typeid(this) != typeid(CheckBox)) {
		delete mesh; mesh = nullptr;
		delete texture; texture = nullptr;
	}	*/
}

void DrawableEntity::init(float layer, vec2& initPos) {
	this->width = texture->getWidthAfterScale();
	this->height = texture->getHeightAfterScale();
	this->scale = texture->getScale();
	this->position = initPos;

	// If not player, otherplayer, weapon or ammunition
	/*if (typeid(this) != typeid(Player) &&
		typeid(this) != typeid(Weapon)) {
		this->mesh = GraphicsUtils::createModelQuad(width, height, layer);
	}*/
}

void DrawableEntity::renderDisplay(mat4& proj) {
	doRender(true, proj);
}

void DrawableEntity::render(mat4& proj) {
	doRender(false, proj);
}

void DrawableEntity::doRender(bool display, mat4& proj) {
	ShaderHandler::standardShader->comeHere();
	glActiveTexture(GL_TEXTURE0);
	if (display) {
		InventoryItem* item = (InventoryItem*) this;
		item->getDisplayTexture()->bind();
	}
	else {
		texture->bind();
	}
	glActiveTexture(GL_TEXTURE1);
	ShadowHandler::bindShadowMap();

	mat4 translation = translate(vec3(position.x, position.y, 0));
	ShaderHandler::standardShader->uploadMatrix(proj, "projMatrix");
	ShaderHandler::standardShader->uploadMatrix(rotation, "rotationMatrix");
	ShaderHandler::standardShader->uploadMatrix(translation, "modelMatrix");
	ShaderHandler::standardShader->uploadFloat(Camera::getWinSizeX(), "windowSizeX");
	ShaderHandler::standardShader->uploadFloat(Camera::getWinSizeY(), "windowSizeY");
	ShaderHandler::standardShader->uploadVec(Camera::getPosition(), "camPos");
	ShaderHandler::standardShader->uploadInt(LightHandler::lightList.size(), "numLights");
	ShaderHandler::standardShader->uploadVec(LightHandler::lightList.at(0), "lightPos");

	mesh->draw();

	if (display) {
		InventoryItem* item = (InventoryItem*) this;
		item->getDisplayTexture()->unbind();
	}
	else {
		texture->unbind();
	}
	
	ShadowHandler::unbindShadowMap();
	ShaderHandler::standardShader->pissOff();
}