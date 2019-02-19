#include "stdafx.h"

#include "Context.h"

namespace Graphics::Context
{


Context* Context::m_pCurrent = nullptr;

Context::Context(Window* pWindow) :
	m_pWindow(pWindow)
{
}

}
