#pragma once
#include "../../Logic/DrawableEntity.h"

class Slider : public DrawableEntity {
public:
	Slider(glm::vec2, float length, float& value);
	~Slider();

	void update();

private:
	float m_length;
	float& m_value;

	bool m_isDragging;
};

