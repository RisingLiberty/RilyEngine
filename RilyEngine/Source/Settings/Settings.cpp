#include "stdafx.h"

#include "Settings.h"

namespace Settings
{
	void Settings::AddSetting(const Setting& setting)
	{
		m_Settings[setting.Name] = setting.Value;
	}

	std::string Settings::GetSetting(const std::string& setting) const
	{
		auto it = m_Settings.find(setting);

		if (it != m_Settings.end())
			return it->second;

		return "";
	}
}