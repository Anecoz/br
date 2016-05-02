#include "LightHandler.h"

vector<vec2> LightHandler::lightList;

LightHandler::LightHandler() {

}

LightHandler::~LightHandler() {
	
}

void LightHandler::init() {
	lightList.push_back(vec2(18.0f, 14.0f));
}
