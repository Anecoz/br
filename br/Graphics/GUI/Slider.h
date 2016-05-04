#pragma once
#include "../../Graphics/GUI/GUIElement.h"

class Slider : public GUIElement {
public:
	Slider(glm::vec2, float length, float& value);
	~Slider();

	void update();

private:
	float m_length;
	float& m_value;
	glm::vec2 offset;
	float MAX;
	float MIN;

	bool m_isDragging;
};

