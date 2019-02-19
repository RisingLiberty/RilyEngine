#include "stdafx.h"

#include "SystemManager.h"

#include "Core/System/Systems.h"

SystemManager::SystemManager()
{
}


SystemManager::~SystemManager()
{
}

int SystemManager::InitializeSystems(int width, int height)
{
	ENGINE_CALL(CreateClock(), "Failed to create clock");
	ENGINE_CALL(CreateRenderer(), "Failed to create renderer");
	ENGINE_CALL(CreateWindow(width, height), "Failed to create window");

	ENGINE_CALL(this->GetClock()->Initialize(), "Failed to initiailize clock");
	ENGINE_CALL(this->GetWindow()->Initialize(), "Failed to initialize window");
	ENGINE_CALL(this->GetRenderer()->Initialize(), "Failed to initialize renderer");

	return OK;
}

void SystemManager::UpdateSystems() const
{
	std::for_each(m_Systems.CBegin(), m_Systems.CEnd(),
		[&](System* pSystem)
	{
		pSystem->Update();
	});
}

void SystemManager::DeleteSystems()
{
	std::for_each(m_Systems.CBegin(), m_Systems.CEnd(),
		[&](System* pSystem)
	{
		SAFE_DELETE(pSystem);
	});
}

System* SystemManager::GetSystem(SystemType type) const
{
	auto it = std::find_if(m_Systems.CBegin(), m_Systems.CEnd(),
		[&](System* pSystem)
	{
		return pSystem->GetType() == type;
	});

	if (it != m_Systems.CEnd())
		return *it;

	return nullptr;
}

int SystemManager::CreateWindow(int width, int height)
{
	Window* pWindow = new Window(width, height, "RilyEngine Demo");
	m_Systems.AddC(pWindow);
	return OK;
}

int SystemManager::CreateClock()
{
	Clock* pClock = new Clock();
	m_Systems.AddC(pClock);
	return OK;
}

int SystemManager::CreateRenderer()
{
//#define BATCH

#if defined BATCH
	Graphics::Rendering::Renderer* pRenderer = new Graphics::Rendering::BatchRenderer(Math::Color(0.2f, 0.2f, 0.8f, 1.0f));
#else
	Graphics::Rendering::Renderer* pRenderer = new Graphics::Rendering::Renderer(Math::Color(0.2f, 0.2f, 0.8f, 1.0f));
#endif
	m_Systems.AddC(pRenderer);
	return OK;
}

Graphics::Rendering::Renderer* SystemManager::GetRenderer() const
{
	return dynamic_cast<Graphics::Rendering::Renderer*>(this->GetSystem(SystemType::RENDERER));
}

Window* SystemManager::GetWindow() const
{
	return dynamic_cast<Window*>(this->GetSystem(SystemType::WINDOW));
}

Clock* SystemManager::GetClock() const
{
	return dynamic_cast<Clock*>(this->GetSystem(SystemType::CLOCK));
}
