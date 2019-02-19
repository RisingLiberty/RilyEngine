#pragma once

#include "../../Helper/Singleton.h"
#undef CreateWindow

enum class SystemType;
class System;

namespace Graphics::Rendering
{
	class Renderer;
}
class Window;
class Clock;

class SystemManager : public Singleton<SystemManager>
{
public:
	SystemManager();
	~SystemManager();

	int InitializeSystems(int width, int height);
	void UpdateSystems() const;
	void DeleteSystems();

	System* GetSystem(SystemType type) const;

	Graphics::Rendering::Renderer* GetRenderer() const;
	Window* GetWindow() const;
	Clock* GetClock() const;

private:
	int CreateWindow(int width, int height);
	int CreateClock();
	int CreateRenderer();

	Container::Vector<System*> m_Systems;
};

