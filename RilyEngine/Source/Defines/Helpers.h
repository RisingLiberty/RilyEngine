#pragma once

#define _(x) #x

#define ASSERT(x, message) if(!(x))\
{\
__debugbreak();\
Debug::Log(Debug::LogType::ERROR, message);\
}


#define ENGINE_CALL(function, message)\
{\
int result = function;\
if (result != OK)\
{\
PUSH_ERROR_ID(message, result);\
return result;\
}\
}

void GLClearError();
bool GLLogCall(const char* glFunction, const char* function, const char* file, int line);

#define GLCall(function)\
	GLClearError();\
	function;\
	ASSERT(GLLogCall(#function, __FUNCTION__, __FILE__, __LINE__),"")
