#include "ShaderHandler.h"
#include <GL\glew.h>
#include <string>

Shader* ShaderHandler::levelShader;
Shader* ShaderHandler::fontShader;

void ShaderHandler::init() {
	levelShader = new Shader("Shaders/level.vert", "Shaders/level.frag");
	fontShader = new Shader("Shaders/font.vert", "Shaders/font.frag");

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
}

void ShaderHandler::cleanUp() {
	delete levelShader;
	levelShader = nullptr;
	delete fontShader;
	fontShader = nullptr;
}