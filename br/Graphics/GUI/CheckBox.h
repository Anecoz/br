#pragma once
#include "../../Graphics/GUI/GUIElement.h"

class CheckBox : public GUIElement {
public:
	CheckBox(glm::vec2 position, int& value);
	~CheckBox();

	void update();
	void setCheckedINT(int checked) { b_isChecked = checked; }
private:
	int& b_isChecked;
};

