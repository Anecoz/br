#version 430

layout (location = 0) in vec2 inPosition;	// PER VERTEX
//layout (location = 1) in vec4 texCoords1;	// PER INSTANCE
//layout (location = 2) in vec4 texCoords2;	// PER INSTANCE
layout (location = 3) in vec2 translation;	// PER INSTANCE
layout (location = 4) in float id;			// PER INSTANCE

out vec2 fragTexCoords;
out vec2 fragWorldCoords;

uniform mat4 projMatrix;
uniform vec2 texAtlasDimensions;
uniform vec2 tileDimensions;

void main() {
    // Calc tex coords
	float imW = float(texAtlasDimensions.x);
	float imH = float(texAtlasDimensions.y);
	float tW = float(tileDimensions.x);
	float tH = float(tileDimensions.y);
	float tilesPerRow = float(imW/tW);
	float topY = float(floor(id/tilesPerRow));
	float leftX = float(id - tilesPerRow * topY);
	topY = (imH / tH) - topY;
    if (inPosition.x == 0.0 && inPosition.y == 0.0) {
		fragTexCoords = vec2(leftX * tH/imW, topY * tH/imH);
        //fragTexCoords = texCoords1.xy;
    }
    else if (inPosition.x == 0.0 && inPosition.y == 1.0) {
		fragTexCoords = vec2(leftX * tH/imW, (topY - 1.0) * tH/imH + 1.0/imH);
        //fragTexCoords = texCoords1.zw;
    }
    else if (inPosition.x == 1.0 && inPosition.y == 0.0) {
		fragTexCoords = vec2((leftX + 1.0) * tH/imW, topY * tH/imH);
        //fragTexCoords = texCoords2.xy;
    }
    else if (inPosition.x == 1.0 && inPosition.y == 1.0) {
		fragTexCoords = vec2((leftX + 1.0) * tH/imW, (topY - 1.0) * tH/imH + 1.0/imH);
        //fragTexCoords = texCoords2.zw;
    }
    fragWorldCoords = vec2(inPosition.x + translation.x, inPosition.y + translation.y);
    gl_Position = projMatrix * vec4(vec3(inPosition.x + translation.x, inPosition.y + translation.y, 0.0), 1.0);
}