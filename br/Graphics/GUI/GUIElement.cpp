#include "GUIElement.h"
#include "../../Utils/MathUtils.h"
#include "../Shaders/ShaderHandler.h"
#include <GL\glew.h>

GUIElement::GUIElement(Texture* texture, IndexedVertexArray* mesh, vec2 position) {
	this->texture = texture;
	this->mesh = mesh;
	this->position = position;
}

GUIElement::~GUIElement() {
	
}

void GUIElement::render() {
	// Convert to opengl coordinates
	vec2 oglCoords;
	MathUtils::GUItoOpenGLCoord(position, &oglCoords);
	ShaderHandler::guiShader->comeHere();
	glActiveTexture(GL_TEXTURE0);
	this->texture->bind();
	glDisable(GL_DEPTH_TEST);

	ShaderHandler::guiShader->uploadVec(oglCoords, "translate");

	this->mesh->draw();

	ShaderHandler::guiShader->pissOff();
	this->texture->unbind();
	glEnable(GL_DEPTH_TEST);
}
