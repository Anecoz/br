#version 430

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 texCoords;

out vec2 fragTexCoords;

uniform vec2 translate;

void main() {
	fragTexCoords = texCoords;
	gl_Position = vec4(inPosition.x + translate.x, inPosition.y + translate.y, 0.0, 1.0);
}