#pragma once

#include "ShadowCasterTexture.h"
#include "../../Logic/Level.h"
#include <vector>
#include <glm\glm.hpp>

using namespace glm;
using std::vector;

class ShadowHandler
{
public:
	ShadowHandler();
	~ShadowHandler();

	static ShadowCasterTexture* shadowCasterTexture;

	static void init();
	static void calcShadowCaster(Level* level);
	static void calcShadowMap(vector<vec2>& lightArr, mat4& proj, Level* level);
	
	static void bindShadowMap();
	static void unbindShadowMap();
};

