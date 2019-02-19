#include "stdafx.h"

#include "WindowSettings.h"

namespace Settings
{


WindowSettings::WindowSettings(const int width, const int height, const std::string& title) :
	Width(width),
	Height(height),
	Title(title)
{
}

}