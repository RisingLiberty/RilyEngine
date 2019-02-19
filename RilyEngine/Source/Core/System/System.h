#pragma once

enum class SystemType
{
	INVALID,
	WINDOW,
	RENDERER,
	CLOCK
};

std::ostream& operator<<(std::ostream& os, const SystemType type);

class System
{
public:
	System(const SystemType type);
	virtual ~System();

	virtual int Initialize();
	virtual int Update() {  return UNOVERRIDEN_METHOD; }
	virtual int Shutdown() { return UNOVERRIDEN_METHOD; }

	SystemType GetType() const { return m_Type; }

protected:
	SystemType m_Type = SystemType::INVALID;
};

