#pragma once
#include "Context.h"

namespace Graphics::Context
{


class OpenGLContext : public Context
{
public:
	OpenGLContext(Window* pWindow);
	virtual ~OpenGLContext();

	int Initialize() override;
	void Show() const override;

	void BindVertexArray(const unsigned int va) override;
	void BindVertexBuffer(const unsigned int vb) override;
	void BindIndexBuffer(const unsigned int ib) override;
	void BindShader(const unsigned int shader) override;

	void Draw(PrimitiveType type, unsigned int nrOfIndices);

private:
	SDL_GLContext m_SdlGLContext;

	unsigned int m_BoundVertexArray;
	unsigned int m_BoundVertexBuffer;
	unsigned int m_BoundIndexBuffer;
	unsigned int m_BoundShader;

};

}
