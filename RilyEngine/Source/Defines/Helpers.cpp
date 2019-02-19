#include "stdafx.h"

#include "Helpers.h"

void GLClearError()
{
	int err = glGetError();
	while (err != GL_NO_ERROR) { err = glGetError(); std::cout << err << "\n"; }
}

bool GLLogCall(const char* glFunction, const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		Debug::Log(Debug::LogType::ERROR, "[OpenGL Error] (", error, ") in function ", function, "\nfile: ", file, "\non line ", line, "\nfail on call to function ", glFunction, "\n");
		return false;
	}
	return true;
}