#pragma once

#include "Settings.h"

class Window;
class Clock;

namespace Settings
{


struct EngineSettings
{
	EngineSettings() = default;
	~EngineSettings();

	void Parse(const Settings& settings);

	Window* pWindow = nullptr;
	Clock* pClock = nullptr;

	uint_t Width = 0;
	uint_t Height = 0;
	float Version = 0.0f;
};

}
