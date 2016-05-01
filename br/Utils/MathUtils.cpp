#include <math.h>

#include "MathUtils.h"
#include "../Graphics/Camera.h"

glm::vec2 MathUtils::screenSpaceToWorld(glm::vec2& screenPoint, int& screenWidth, int& screenHeight, glm::mat4& viewProj) {
	double x = 2.0 * (double)screenPoint.x / (double)screenWidth - 1.0;
	double y = -2.0 * (double)screenPoint.y / (double)screenHeight + 1.0;
	glm::mat4 invProj = glm::inverse(viewProj);

	screenPoint.x = (float)x;
	screenPoint.y = (float)y;
	glm::vec4 temp(screenPoint.x, screenPoint.y, 0.0f, 1.0f);
	temp = invProj * temp;
	return glm::vec2(temp.x, temp.y);
}
glm::vec2 MathUtils::screenSpaceToGUI(glm::vec2& screenPoint) {
	float x = screenPoint.x / (float)1280;  // TODO: GET SCREEN SIZE FROM OPTIONS FILE
	float y = screenPoint.y / (float)720;
	return glm::vec2(x, y);
}
bool MathUtils::isWithingGUIBox(glm::vec2& guiPoint, float& x, float& y, float& width, float& height) {
	bool out = false;
	if (guiPoint.x >= x && guiPoint.x <= x + width) {
		if (guiPoint.y >= y && guiPoint.y <= y + height)
			out = true;
	}
	return out;
}
bool MathUtils::screenPointWithinInventory(glm::vec2& screenPoint, glm::vec2& inventoryPosition, float& baseScale) {
	glm::vec2 mouseGUI = screenSpaceToGUI(screenPoint);
	// Get inventory dimensions in GUI coordinates
	float inventoryWidth = baseScale / Camera::getWinSizeX();
	float inventoryHeight = baseScale / Camera::getWinSizeY();

	bool out = false;

	if (mouseGUI.x <= inventoryPosition.x + inventoryWidth && mouseGUI.x >= inventoryPosition.x) {
		if (mouseGUI.y <= inventoryPosition.y + inventoryHeight && mouseGUI.y >= inventoryPosition.y)
			out = true;
	}

	return out;
}
int MathUtils::getInventoryItemIndex(glm::vec2& mousePosition, glm::vec2& position, float& baseScale, int& itemPerRow) {
	glm::vec2 mFix = MathUtils::screenSpaceToGUI(mousePosition) - position;
	double itemWidth = (double)baseScale / (double)(Camera::getWinSizeX()*(double)itemPerRow);
	double itemHeight = (double)baseScale / (double)(Camera::getWinSizeY()*(double)itemPerRow);
	int indX = (int)floor((double)mFix.x / itemWidth);
	int indY = (int)floor((double)mFix.y / itemHeight);
	
	return indX + itemPerRow*indY;
}