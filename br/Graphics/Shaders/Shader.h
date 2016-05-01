#pragma once

#include <GL\glew.h>
#include <string>
#include <glm\glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

class Shader
{
public:
	Shader();
	Shader(string vertPath, string fragPath);
	~Shader();

	static const GLint VERTEX_ATTRIB_LOC = 0;
	static const GLint TEX_ATTRIB_LOC = 1;

	GLuint getId();
	void comeHere();
	void pissOff();

	// ---------UPLOADS--------
	void uploadFloat(GLfloat val, string name);
	void uploadInt(GLint val, string name);
	void uploadVec(vec4& vec, string name);
	void uploadVec(vec3& vec, string name);
	void uploadVec(vec2& vec, string name);
	void uploadVecArr(vector<vec2>& vecArr, string name);
	void uploadBool(GLboolean val, string name);
	void uploadTexture(GLint texUnit, string name);
	void uploadMatrix(mat4& mat, string name);

private:
	GLuint id;
};

