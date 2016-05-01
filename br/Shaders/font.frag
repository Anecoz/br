#version 430

in vec2 texcoord;
out vec4 outColor;
uniform sampler2D tex;
uniform vec4 color;

void main(void) {
	outColor = vec4(1, 1, 1, texture(tex, texcoord).r) * color;
}