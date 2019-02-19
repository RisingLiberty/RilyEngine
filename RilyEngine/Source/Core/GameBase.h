#pragma once

#include "../Settings/EngineSettings.h"

namespace Core
{
	class Engine;

	class GameBase
	{
	public:
		GameBase(const std::string& name, const Settings::EngineSettings& settings);
		virtual ~GameBase();

		virtual void Start() = 0;

	protected:
		virtual int Initialize();
		virtual void Update();
		virtual void Shutdown();

	protected:
		std::string m_Name;
		Engine* m_pEngine = nullptr;
	};

}

