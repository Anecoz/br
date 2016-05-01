#pragma once
#include "../Tmx/Tmx.h"
#include <iostream>

using namespace std;
using namespace Tmx;

class LevelUtils {

public:
	static void printMapInfo(Map* map);
	static void setTileTexCoords(Map* map);

};