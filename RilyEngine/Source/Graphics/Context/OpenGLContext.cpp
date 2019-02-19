#include "stdafx.h"

#include "OpenGLContext.h"

#include "Core/System/Window.h"

#include "Graphics/Shaders/ShaderProgram.h"

namespace Graphics::Context
{


void GLAPIENTRY MessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	Debug::Log(Debug::LogType::ERROR,
		"Source: ", source, "\n",
		"Type: ", type, "\n",
		"Severity: ", severity, "\n",
		"Message: ", message);
}

OpenGLContext::OpenGLContext(Window* pWindow) :
	Context(pWindow)
{
	m_SdlGLContext = SDL_GL_CreateContext(pWindow->GetSdlHandle());
	if (m_SdlGLContext == NULL)
		PUSH_ERROR(SDL_GetError());

	SDL_GL_SetSwapInterval(1);
}

OpenGLContext::~OpenGLContext()
{
	SDL_GL_DeleteContext(m_SdlGLContext);
}

int OpenGLContext::Initialize()
{
	int result = glewInit();
	if (result != GLEW_OK)
		PUSH_ERROR_ID("Could not initialize GLEW!", result);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	Debug::Log(Debug::LogType::INFO, "Open GL version: ", glGetString(GL_VERSION));

	glEnable(GL_DEBUG_OUTPUT);
	GLCall(glDebugMessageCallback(MessageCallback, 0));

	Context::m_pCurrent = this;

	return result;
}

void OpenGLContext::Show() const
{
	SDL_GL_SwapWindow(m_pWindow->GetSdlHandle());
}

void OpenGLContext::BindVertexArray(const unsigned int va)
{
	if (m_BoundVertexArray == va)
		Debug::Log(Debug::LogType::WARNING, "Vertex array with id ", va, " already bound!");

	else
	{
		m_BoundVertexArray = va;
		GLCall(glBindVertexArray(va));
	}
}

void OpenGLContext::BindVertexBuffer(const unsigned int vb)
{	
	if (m_BoundVertexArray == vb)
		Debug::Log(Debug::LogType::WARNING, "Vertex buffer with id ", vb, " already bound!");

	m_BoundVertexArray = vb;
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb));
}

void OpenGLContext::BindIndexBuffer(const unsigned int ib)
{
	if (m_BoundVertexArray == ib)
		Debug::Log(Debug::LogType::WARNING, "Index buffer with id ", ib, " already bound!");

	m_BoundVertexArray = ib;
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib));
}

void OpenGLContext::BindShader(const unsigned int shader)
{
	if (m_BoundVertexArray == shader)
		Debug::Log(Debug::LogType::WARNING, "Shader with id ", shader, " already bound!");

	m_BoundVertexArray = shader;
	GLCall(glUseProgram(shader));
}

void OpenGLContext::Draw(PrimitiveType type, unsigned int nrOfIndices)
{
	switch (type)
	{
	case Graphics::PrimitiveType::TRIANGLES:
		GLCall(glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0));
		break;
	default:
		Debug::Log(Debug::LogType::WARNING, "Unspecified primitive type to draw");
		break;
	}
}

}
