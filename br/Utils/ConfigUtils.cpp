#include "ConfigUtils.h"

#include <stdio.h>
#include <errno.h>

int ConfigUtils::VSYNC;
int ConfigUtils::WIDTH;
int ConfigUtils::HEIGHT;
float ConfigUtils::VOLUME;

CSimpleIniA ConfigUtils::ini(true, false, false);

bool ConfigUtils::readConfig() {
	ConfigUtils::ini.SetUnicode();
	std::string file = "Config/config.ini";
	SI_Error rc = ConfigUtils::ini.LoadFile(file.c_str());
	if (rc < 0) {
		printf("Error opening file: %s\n", strerror(errno));
		return false;
	}
	CSimpleIniA::TNamesDepend sections;
	ConfigUtils::ini.GetAllSections(sections);
	CSimpleIniA::TNamesDepend keys;
	CSimpleIniA::TNamesDepend::const_iterator i;
	for (i = sections.begin(); i != sections.end(); ++i) {
		printf("Section-name = '%s'\n", i->pItem);
		ConfigUtils::ini.GetAllKeys(i->pItem, keys);
	}

	// VIDEO section
	ConfigUtils::VSYNC = std::stoi(ConfigUtils::ini.GetValue("VIDEO", "vsync", "1"));
	ConfigUtils::WIDTH = std::stoi(ConfigUtils::ini.GetValue("VIDEO", "width", "1280"));
	ConfigUtils::HEIGHT = std::stoi(ConfigUtils::ini.GetValue("VIDEO", "height","720"));
	// SOUND section
	ConfigUtils::VOLUME = std::stof(ConfigUtils::ini.GetValue("SOUND", "volume", "0.5"));

	return true;
}
bool ConfigUtils::saveConfig() {
	std::string file = "Config/config.ini";
	SI_Error rc = ConfigUtils::ini.SaveFile(file.c_str());
	if (rc < 0) {
		printf("Error opening file: %s\n", strerror(errno));
		return false;
	}
	return true;
}

std::string ConfigUtils::getValue(std::string section, std::string key) {
	return ConfigUtils::ini.GetValue(section.c_str(), key.c_str(), NULL);
}

bool ConfigUtils::setValue(std::string section, std::string key, std::string value) {
	SI_Error rc = ConfigUtils::ini.SetValue(section.c_str(), key.c_str(), value.c_str());
	if (rc < 0) {
		printf("Error opening file: %s\n", strerror(errno));
		return false;
	}
	printf("key: %s\n", rc == SI_INSERTED ?	"inserted" : "updated");
	return true;
}

void ConfigUtils::setAllValues() {
	// VIDEO section
	setValue("VIDEO", "vsync", std::to_string(ConfigUtils::VSYNC).c_str());
	setValue("VIDEO", "width", std::to_string(ConfigUtils::WIDTH).c_str());
	setValue("VIDEO", "height", std::to_string(ConfigUtils::HEIGHT).c_str());
	// SOUND section
	setValue("SOUND", "volume", std::to_string(ConfigUtils::VOLUME).c_str());
}