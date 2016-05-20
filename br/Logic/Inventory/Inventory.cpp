#include "Inventory.h"
#include "../../Graphics/Shaders/ShaderHandler.h"
#include "../../Graphics/Camera.h"
#include "../../Utils/GraphicsUtils.h"
#include "../../Utils/MathUtils.h"
#include "../../Input/KeyInput.h"
#include "../../Input/MousePosInput.h"
#include "../../Input/MouseButtonInput.h"

#include <algorithm>
#include <glm\gtx\transform.hpp>

vector<InventoryItem*> Inventory::inventoryItems;
Weapon* Inventory::m_equipedWeapon;

Inventory::Inventory() {
	m_backgroundQuad = GraphicsUtils::createInventoryQuad();
	m_position = vec2(0.4f);
	m_baseScale = 4.0f;
	ITEMS_PER_ROW = 5;
	m_inventorySpace = ITEMS_PER_ROW * ITEMS_PER_ROW;
	m_equipedWeapon = nullptr;
}

void Inventory::update(Level* level) {
	checkInput(level);
}

void Inventory::checkInput(Level* level) {
	if (KeyInput::isKeyClicked(GLFW_KEY_G)) {
		m_isOpen = !m_isOpen;
	}

	vec2 mousePos = MousePosInput::getPosition();
	if (MouseButtonInput::isMouseLeftDown()) {
		if (m_isOpen && MathUtils::screenPointWithinInventory(mousePos, m_position, m_baseScale)) {
			int listIndex = MathUtils::getInventoryItemIndex(mousePos, m_position, m_baseScale, ITEMS_PER_ROW);
			if (inventoryItems.size() >= listIndex + 1) {
				InventoryItem* item = inventoryItems[listIndex];
				if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
					m_equipedWeapon = weapon;
				}
			}
		}
	}
	// Check if we right clicked and are trying to throw something out
	if (MouseButtonInput::isMouseButtonClicked(GLFW_MOUSE_BUTTON_2)) {
		if (m_isOpen && MathUtils::screenPointWithinInventory(mousePos, m_position, m_baseScale)) {
			// Get what item we clicked on
			int listIndex = MathUtils::getInventoryItemIndex(mousePos, m_position, m_baseScale, ITEMS_PER_ROW);
			if (inventoryItems.size() >= listIndex + 1) {
				InventoryItem* item = inventoryItems[listIndex];
				if (m_equipedWeapon == item) {
					m_equipedWeapon = nullptr;
				}
				item->setRotation(mat4());
				item->setPosition(item->getPosition());
				level->addDroppedItem(item);
				remove(item);
				// Send network notification that we dropped this shit
				//ClientSender.addItemToWorld(item);
			}
		}
	}

	// Check the dragging status of the whole window
	if (!m_isDragging) {
		if (m_isOpen && MouseButtonInput::isMouseLeftDown() &&
			MathUtils::screenPointWithinInventory(mousePos, m_position, m_baseScale)) {
			m_offset = MathUtils::screenSpaceToGUI(mousePos) - m_position;
			m_isDragging = true;
		}
	}
	else if (m_isOpen) {
		// Check if we've let go
		if (!MouseButtonInput::isMouseLeftDown()) {
			m_isDragging = false;
		}
		else {
			m_position = MathUtils::screenSpaceToGUI(mousePos) - m_offset;
		}
	}
}

void Inventory::add(InventoryItem* item) {
	if (m_equipedWeapon == nullptr) {
		if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
			m_equipedWeapon = weapon;
		}
	}
	inventoryItems.push_back(item);
}

void Inventory::remove(InventoryItem* item) {
	inventoryItems.erase(std::remove(inventoryItems.begin(), inventoryItems.end(), item), inventoryItems.end());
}

void Inventory::render(mat4& projMatrix) {
	if (m_equipedWeapon != nullptr)
		m_equipedWeapon->render(projMatrix);

	if (m_isOpen) {
		prepareRender();

		// Get world coordinates
		vec2 renderWorldPos;
		renderWorldPos.x = Camera::getPosition().x + m_position.x * Camera::getWinSizeX();
		renderWorldPos.y = Camera::getPosition().y + m_position.y * Camera::getWinSizeY();

		mat4 translation = translate(vec3(renderWorldPos.x, renderWorldPos.y, 0));
		ShaderHandler::inventoryShader->uploadMatrix(projMatrix, "projMatrix");
		ShaderHandler::inventoryShader->uploadMatrix(translation, "modelMatrix");
		ShaderHandler::inventoryShader->uploadInt(ITEMS_PER_ROW, "itemsPerRow");
		ShaderHandler::inventoryShader->uploadFloat(m_baseScale, "scale");
		ShaderHandler::inventoryShader->uploadFloat(m_baseScale, "baseScale");
		ShaderHandler::inventoryShader->uploadInt(1, "isBackground");
		m_backgroundQuad->draw();

		ShaderHandler::inventoryShader->uploadInt(0, "isBackground");
		for (int index = 0; index < inventoryItems.size(); index++) {
			inventoryItems[index]->getDisplayTexture()->bind();
			ShaderHandler::inventoryShader->uploadMatrix(translation, "modelMatrix");
			ShaderHandler::inventoryShader->uploadInt(index, "itemIndex");
			ShaderHandler::inventoryShader->uploadFloat(m_baseScale / (float)ITEMS_PER_ROW, "scale");
			inventoryItems[index]->getMesh()->draw();
		}

		finishRender();
	}
}

void Inventory::prepareRender() {
	ShaderHandler::inventoryShader->comeHere();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
}

void Inventory::finishRender() {
	ShaderHandler::inventoryShader->pissOff();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

Inventory::~Inventory() {
	for (InventoryItem* item : inventoryItems) {
		delete item;
		item = nullptr;
	}
	inventoryItems.clear();

	delete m_backgroundQuad;
	m_backgroundQuad = nullptr;

	delete m_equipedWeapon;
	m_equipedWeapon = nullptr;
}