#include "stdafx.h"

#include "Engine.h"

#include "GameBase.h"

#include "Managers/InputManager.h"
#include "Managers/ResourceManager.h"
#include "Managers/SystemManager.h"
#include "Managers/SceneManager.h"
#include "Managers/ShaderManager.h"

#include "System/Window.h"

#include "Debug/Logger.h"

#include "Settings/EngineSettings.h"

namespace Core
{


Engine::Engine(GameBase* pGame):
	Count(1),
	m_pGame(pGame)
{
	ChangeState(EngineState::CONSTRUCTING, "Engine is constructing");
}


Engine::~Engine()
{
}

int Engine::Initialize(const Settings::EngineSettings& settings)
{
	this->ChangeState(EngineState::INITIALIZING, "Engine is initializing");
	ENGINE_CALL(SDL_Init(SDL_INIT_VIDEO), "Failed to initialize SDL");
	ENGINE_CALL(InitializeManagers(settings), "Failed to initialize manager");

	Debug::NewLine();
	Debug::Log(Debug::LogType::INFO, "Engine Version: ", settings.Version);
	Debug::Log(Debug::LogType::INFO, "Date: ", TimeAndDateToString());
	Debug::NewLine();

	return OK;
}

int Engine::InitializeManagers(const Settings::EngineSettings& settings) const
{
	ENGINE_CALL(Memory::MemoryManager::Initialize(),"Failed to initialize Memory Manager");
	ENGINE_CALL(Debug::Logger::Initialize(), "Failed to initialize Logger");
	EventHandler::CreateInstance();
	InputManager::CreateInstance();
	SystemManager::CreateInstance();
	ENGINE_CALL(SystemManager::GetInstance()->InitializeSystems(settings.Width, settings.Height), "");
	SceneManager::CreateInstance();
	ResourceManager::CreateInstance();
	ResourceManager::GetInstance()->Initialize();
	ShaderManager::CreateInstance();
	ShaderManager::GetInstance()->Initialize();

	return OK;
}

int Engine::Update()
{
	SystemManager::GetInstance()->UpdateSystems();

	int result = EventHandler::GetInstance()->Update();
	return result;
}

void Engine::Shutdown()
{
	ShaderManager::DestroyInstance();
	SystemManager::GetInstance()->DeleteSystems();
	SystemManager::DestroyInstance();
	InputManager::DestroyInstance();
	EventHandler::DestroyInstance();
	SceneManager::DestroyInstance();
	ResourceManager::DestroyInstance();

	Debug::Logger::Shutdown();

	//this needs to be destroyed last
	Memory::MemoryManager::Shutdown();
}

void Engine::ChangeState(const EngineState& state, const std::string& message)
{
	m_State = state;
	Debug::Log(Debug::LogType::FORCE, "--------------------\n", message, "\n--------------------");
	std::stringstream ss;
	ss << "<" << TimeAndDateToString() << "> " << message;
	PUSH_INFO(ss.str());
}

}
