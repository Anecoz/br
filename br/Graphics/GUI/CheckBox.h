#pragma once
#include <glm\glm.hpp>

class CheckBox {
public:
	CheckBox(glm::vec2 position, bool& value);
	~CheckBox();

	void update();
	void setChecked(bool checked) { m_isChecked = checked; }
private:
	glm::vec2 m_position;
	bool& m_isChecked;
};

