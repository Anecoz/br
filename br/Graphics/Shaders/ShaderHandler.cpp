#include "ShaderHandler.h"
#include <GL\glew.h>
#include <string>

Shader* ShaderHandler::levelShader;
Shader* ShaderHandler::fontShader;
Shader* ShaderHandler::shadowMapShader;

void ShaderHandler::init() {
	levelShader = new Shader("Shaders/level.vert", "Shaders/level.frag");
	fontShader = new Shader("Shaders/font.vert", "Shaders/font.frag");
	shadowMapShader = new Shader("Shaders/shadows/shadowMap.vert", "Shaders/shadows/shadowMap.frag");

	fontShader->comeHere();
	glActiveTexture(GL_TEXTURE0);
	fontShader->uploadTexture(0, std::string("tex"));
	fontShader->pissOff();

	levelShader->comeHere();
	glActiveTexture(GL_TEXTURE0);
	levelShader->uploadTexture(0, std::string("atlas"));
	glActiveTexture(GL_TEXTURE1);
	levelShader->uploadTexture(1, std::string("shadowTex"));
	levelShader->pissOff();

	shadowMapShader->comeHere();
	shadowMapShader->uploadTexture(0, "collisionMap");
	shadowMapShader->pissOff();
}

void ShaderHandler::cleanUp() {
	delete levelShader;	levelShader = nullptr;
	delete fontShader;	fontShader = nullptr;
	delete shadowMapShader; shadowMapShader = nullptr;
}