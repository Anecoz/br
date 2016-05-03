#pragma once
#include <GL\glew.h>
#include "../Lowlevel/Fbo.h"
#include "../Lowlevel/IndexedVertexArray.h"
#include "../../Logic/Level.h"
#include "../../Logic/Player.h"
#include <vector>
#include <glm\glm.hpp>

using namespace glm;
using std::vector;

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	static GLuint shadowMapID;

	static void init();
	static void calcShadowMap(vector<vec2>& lightArr, mat4& proj, Level* level, Player* player);

private:
	static Fbo* fbo;
	static IndexedVertexArray* quad;
};

