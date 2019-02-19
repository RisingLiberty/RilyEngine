#pragma once

namespace Settings
{
	struct EngineSettings;
}

namespace Resources
{


	class ResourceLoader
	{
	public:
		ResourceLoader() = delete;
		~ResourceLoader() = delete;

		static Settings::EngineSettings LoadGameSettings(const std::string& path);

	private:
	};
}