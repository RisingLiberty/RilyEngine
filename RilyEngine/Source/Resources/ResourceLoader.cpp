#include "stdafx.h"

#include "ResourceLoader.h"

#include "Files\TextFile.h"

#include "Settings/Settings.h"

namespace Resources
{
	Settings::EngineSettings ResourceLoader::LoadGameSettings(const std::string& path)
	{
		TextFile file(path);

		if (!file.Exists())
		{
			ASSERT(false, "<Load Game Settings> No valid file path given!");
			return {};
		}

		Settings::Settings settings;

		file.Open(std::ios::in);

		while (!file.EndOfFile())
		{
			std::string line = file.ReadLine();
			settings.AddSetting(Settings::Setting(line));
		}

		Settings::EngineSettings gameSettings;
		gameSettings.Parse(settings);

		return gameSettings;
	}
}