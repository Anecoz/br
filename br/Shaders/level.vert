#version 430

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec4 texCoords1;
layout (location = 2) in vec4 texCoords2;

out vec2 fragTexCoords;
out vec2 fragWorldCoords;

//uniform vec4 texCoords1;
//uniform vec4 texCoords2;
uniform mat4 projMatrix;
uniform float windowSizeX;
//uniform mat4 translationMatrix;

void main() {
    // Calc tex coords
    if (inPosition.x == 0.0 && inPosition.y == 0.0) {
        fragTexCoords = texCoords1.xy;
    }
    else if (inPosition.x == 0.0 && inPosition.y == 1.0) {
        fragTexCoords = texCoords1.zw;
    }
    else if (inPosition.x == 1.0 && inPosition.y == 0.0) {
        fragTexCoords = texCoords2.xy;
    }
    else if (inPosition.x == 1.0 && inPosition.y == 1.0) {
        fragTexCoords = texCoords2.zw;
    }
	// Calc translation
	int dy = int(floor(gl_InstanceID/int(windowSizeX)));
	int dx = gl_InstanceID - int(windowSizeX)*dy;
    fragWorldCoords = vec2(inPosition.x + dx, inPosition.y + dy);
    gl_Position = projMatrix * vec4(vec3(inPosition.x + dx, inPosition.y + dy, 0.0), 1.0);
}