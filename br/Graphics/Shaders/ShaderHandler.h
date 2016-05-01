#pragma once

#include "Shader.h"

class ShaderHandler {
public:
	static Shader* levelShader;
	static Shader* fontShader;

	static void init();

	static void cleanUp();
};
