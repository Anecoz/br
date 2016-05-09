#pragma once
#include <vector>

#include "../../Graphics/Lowlevel/IndexedVertexArray.h"
#include "../Level.h"
#include "../Weapons/Weapon.h"
#include "InventoryItem.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	void update(Level* level);
	void checkInput(Level* level);
	void add(InventoryItem* item);
	void remove(InventoryItem* item);
	void render(mat4& projMatrix);
	void prepareRender();
	void finishRender();

	static vector<InventoryItem*> inventoryItems;

	bool isDragging() { return m_isDragging; }
	Weapon* getEquipedWeapon() { return m_equipedWeapon; }
	void setEquipedWeapon(Weapon* weapon) { m_equipedWeapon = weapon; }

private:
	IndexedVertexArray* m_backgroundQuad;
	int ITEMS_PER_ROW;
	int m_inventorySpace;
	bool m_isOpen;
	bool m_isDragging;
	glm::vec2 m_position;
	glm::vec2 m_offset;
	float m_baseScale;
	static Weapon* m_equipedWeapon;
};

