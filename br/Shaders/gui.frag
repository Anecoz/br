#version 430

out vec4 outColor;

in vec2 fragTexCoords;

uniform sampler2D tex;

void main() {
	vec4 col = texture(tex, vec2(fragTexCoords.x, fragTexCoords.y));
    if (col.a < 0.5) {
        discard;
    }

    outColor = col;
}