#pragma once

#include "../../Helper/Singleton.h"

class EventHandler : public Singleton<EventHandler>
{
public:
	int Update();

	int ProcessEvent(const SDL_Event& event);
private:
};

