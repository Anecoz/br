#pragma once

#include "Shader.h"

class ShaderHandler {
public:
	static Shader* levelShader;
	static Shader* fontShader;
	static Shader* shadowMapShader;
	static Shader* standardShader;

	static void init();

	static void cleanUp();
};
