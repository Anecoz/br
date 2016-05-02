#include "ShadowMap.h"
#include "../../Utils/GraphicsUtils.h"
#include "../Shaders/ShaderHandler.h"
#include "../Camera.h"
#include "ShadowHandler.h"
#include <glm\gtx\transform.hpp>

Fbo* ShadowMap::fbo;
IndexedVertexArray* ShadowMap::quad;
GLuint ShadowMap::shadowMapID;

ShadowMap::ShadowMap() {

}

ShadowMap::~ShadowMap() {
	delete fbo; fbo = nullptr;
	delete quad; quad = nullptr;
}

void ShadowMap::init() {
	fbo = new Fbo(1280, 720);
	quad = GraphicsUtils::createSimpleQuad();
}

void ShadowMap::calcShadowMap(vector<vec2>& lightArr, mat4& proj, Level* level) {
	fbo->bind();
	glDisable(GL_DEPTH_TEST);
	ShaderHandler::shadowMapShader->comeHere();

	mat4 modelMatrix = glm::translate(vec3(Camera::getPosition().x, Camera::getPosition().y, 0.0f));
	mat4 scaleMatrix = glm::scale(vec3(Camera::getWinSizeX(), Camera::getWinSizeY(), 1.0f));
	ShaderHandler::shadowMapShader->uploadMatrix(proj, "projMatrix");
	ShaderHandler::shadowMapShader->uploadMatrix(modelMatrix * scaleMatrix, "modelMatrix");
	ShaderHandler::shadowMapShader->uploadInt(1, "numLights");
	ShaderHandler::shadowMapShader->uploadVec(lightArr.at(0), "lightPos");
	ShaderHandler::shadowMapShader->uploadVec(vec2(10), "playerPos");
	ShaderHandler::shadowMapShader->uploadInt(level->getWidth(), "worldWidth");
	ShaderHandler::shadowMapShader->uploadInt(level->getHeight(), "worldHeight");
	ShaderHandler::shadowMapShader->uploadInt((int)Camera::getWinSizeX(), "windowSize");
	ShadowHandler::shadowCasterTexture->bind();

	quad->draw();

	ShaderHandler::shadowMapShader->pissOff();
	ShadowHandler::shadowCasterTexture->unbind();
	glEnable(GL_DEPTH_TEST);
	fbo->unbind();

	shadowMapID = fbo->getColourTextureId();
}
