#include "stdafx.h"

#include "System.h"

#include "Core/Managers/SystemManager.h"

std::ostream& operator<<(std::ostream& os, const SystemType type)
{
	os << (int)type;
	return os;
}

System::System(const SystemType type):
	m_Type(type)
{
}


System::~System()
{
}

int System::Initialize()
{
	//SystemManager::GetInstance()->AddSystem(this);
	return OK;
}
