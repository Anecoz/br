#pragma once
#include <glm\glm.hpp>

class MathUtils
{
public:
	static glm::vec2 screenSpaceToWorld(glm::vec2& screenPoint, int& screenWidth, int& screenHeight, glm::mat4& viewProj);
	static glm::vec2 screenSpaceToGUI(glm::vec2& screenPoint);
	static bool isWithingGUIBox(glm::vec2& guiPoint, float& x, float& y, float& width, float& height);
	static bool screenPointWithinInventory(glm::vec2& screenPoint, glm::vec2& inventoryPosition, float& baseScale);
	static int getInventoryItemIndex(glm::vec2& mousePosition, glm::vec2& position, float& baseScale, int& itemPerRow);
};
