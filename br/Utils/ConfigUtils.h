#pragma once
#include <SimpleIni.h>
#include <string.h>

class ConfigUtils
{
public:
	static bool readConfig();
	static bool saveConfig();
	static std::string getValue(std::string section, std::string key);
	static bool setValue(std::string section, std::string key, std::string value);
	static void setAllValues();

	// Config attributes
	// [VIDEO]
	static int VSYNC;
	static int WIDTH;
	static int HEIGHT;
	// [SOUND]
	static float VOLUME;

	// Pointer to the config file
	static CSimpleIniA ini;
};

