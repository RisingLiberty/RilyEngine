#pragma once


#include "Graphics/PrimitiveType.h"

namespace Graphics::Context
{

class Context
{
public:
	Context(Window* pWindow);
	~Context() = default;

	virtual int Initialize() = 0;
	virtual void Show() const = 0;

	virtual void BindVertexArray(const unsigned int va) = 0;
	virtual void BindVertexBuffer(const unsigned int vb) = 0;
	virtual void BindIndexBuffer(const unsigned int ib) = 0;
	virtual void BindShader(const unsigned int shader) = 0;

	virtual void Draw(PrimitiveType type, unsigned int nrOfIndices) = 0;


	static Context* GetCurrent() { return m_pCurrent; }

protected:
	static Context* m_pCurrent;
	Window * m_pWindow;
};

}
