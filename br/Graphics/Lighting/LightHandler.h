#pragma once

#include <vector>
#include <glm\glm.hpp>

using std::vector;
using glm::vec2;

class LightHandler
{
public:
	LightHandler();
	~LightHandler();

	static void init();

	static vector<vec2> lightList;
};

