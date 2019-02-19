#pragma once

//errors --> +
//ok --> 0
//warnings --> -

#define OK 0

//window errors
#define FAILED_TO_INITIALIZE_WINDOW 1
#define FAILED_TO_SETUP_WINDOW 2
#define FAILED_TO_CREATE_WINDOW_SDL 3

//glfw errors
#define FAILED_TO_INITIALIZE_GLFW 1

//DirectX errors
#define DIRECTX_VERSION_NOT_SUPPORTED 1

//Render target errors
#define RENDER_TARGET_INVALID 1

//Input errors
#define FAILED_TO_INITIALIZE_SDL 1

//Shader errors
#define UNIFORM_NOT_FOUND -1

//Clock errors
#define PAUSED -1

//Game errors
#define SYSTEM_UNDEFINED 1

//Event returns
#define QUIT -1

//Method warnings
#define UNOVERRIDEN_METHOD -1

//Resource warnings
#define COULD_NOT_OPEN_RESOURCE -1