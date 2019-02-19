#include "stdafx.h"

#include "EngineSettings.h"

#include "../Core/System/Clock.h"
#include "../Core/System/Window.h"

namespace Settings
{

	namespace
	{
		const std::string WIDTH = "width";
		const std::string HEIGHT = "height";
		const std::string VERSION = "version";
	}

EngineSettings::~EngineSettings()
{
}

void EngineSettings::Parse(const Settings& settings)
{
	Width = std::stoi(settings.GetSetting(WIDTH));
	Height = std::stoi(settings.GetSetting(HEIGHT));
	Version = std::stof(settings.GetSetting(VERSION));
}

}
