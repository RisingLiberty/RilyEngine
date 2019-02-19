#pragma once

#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

class Clock : public System, public Count<Clock>
{
public:
	Clock();
	~Clock();
	
	int Initialize() override;
	int Update() override;


	void Start();
	void Pause();

	float GetCurrentTime();
	float GetDeltaTime() const { return m_DeltaTime; }
	float GetFPS() const { return 1 / m_DeltaTime; }
	
private:
	uint_t m_StartTime = 0;
	uint_t m_StartPauseTime = 0;
	uint_t m_CurrentTime = 0;
	float m_DeltaTime = 0;
	bool m_IsPaused = false;
};

