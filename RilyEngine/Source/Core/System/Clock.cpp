#include "stdafx.h"

#include <chrono>

#include "Clock.h"

const int TICKS_PER_SECOND = 1000;

Clock::Clock():
	System(SystemType::CLOCK),
	Count(1)
{
}


Clock::~Clock()
{
}

int Clock::Initialize()
{
	System::Initialize();
	m_StartTime = SDL_GetTicks();
	m_CurrentTime = m_StartTime;
	m_StartPauseTime = -1;
	srand(GetTickCount());
	return OK;
}

int Clock::Update()
{

	if (m_IsPaused)
		return PAUSED;

	auto prevTime = m_CurrentTime;
	m_CurrentTime = SDL_GetTicks();
	m_DeltaTime = float(m_CurrentTime - prevTime) / TICKS_PER_SECOND;

	return OK;
}

void Clock::Start()
{
	m_IsPaused = false;
}

void Clock::Pause()
{
	m_StartPauseTime = SDL_GetTicks();
	m_DeltaTime = 0;
	m_IsPaused = true;
}


float Clock::GetCurrentTime()
{
	return (float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}