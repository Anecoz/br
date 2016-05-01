#version 430

layout (location = 0) in vec2 inPosition;
//layout (location = 1) in vec2 texCoords;

out vec2 fragTexCoords;
out vec2 fragWorldCoords;

uniform vec4 texCoords1;
uniform vec4 texCoords2;
uniform mat4 projMatrix;
uniform mat4 translationMatrix;

void main() {
    /*fragTexCoords = texCoords;
    fragWorldCoords = inPosition.xy;
    gl_Position = projMatrix * vec4(inPosition, 1.0);*/
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
    fragWorldCoords = (translationMatrix * vec4(vec3(inPosition.x, inPosition.y, 0.0), 1.0)).xy;
    gl_Position = projMatrix * translationMatrix * vec4(vec3(inPosition.x, inPosition.y, 0.0), 1.0);
	//gl_Position = vec4(inPosition.x, inPosition.y, 0.0, 1.0);
}