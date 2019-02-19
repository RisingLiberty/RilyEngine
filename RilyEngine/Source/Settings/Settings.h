#pragma once

namespace Settings
{
	struct Setting
	{
		Setting(const std::string& line)
		{
			Name = line.substr(1, line.find_first_of('>') - 1);
			Value = line.substr(line.find_first_of('>') + 1);
		}

		std::string Name;
		std::string Value;
	};

	class Settings
	{
	public:
		void AddSetting(const Setting& setting);

		std::string GetSetting(const std::string& setting) const;

	private:
		std::map<std::string, std::string> m_Settings;
	};
}