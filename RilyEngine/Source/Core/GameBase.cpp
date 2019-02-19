#include "stdafx.h"

#include "GameBase.h"

#include "Engine.h"

#include "Managers/SystemManager.h"
#include "System/Systems.h"

namespace Core
{
	GameBase::GameBase(const std::string& name, const Settings::EngineSettings& settings) :
		m_Name(name)
	{
		m_pEngine = new Engine(this);
		m_pEngine->Initialize(settings);
	}

	GameBase::~GameBase()
	{
		SAFE_DELETE(m_pEngine);
	}

	int GameBase::Initialize()
	{
		return OK;
	}

	void GameBase::Update()
	{
		m_pEngine->Update();
	}

	void GameBase::Shutdown()
	{
		m_pEngine->Shutdown();
	}
}

