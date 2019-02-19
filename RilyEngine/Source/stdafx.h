#pragma once
//C++ standard includes
#include <string>
//#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <list>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <functional>

//Windows includes
#include <Windows.h>
#include <Windowsx.h>

//DirectX includes
#if 0 
#if defined _WIN32 || defined _WIN64

#include <dxgi.h>
#pragma comment(lib, "dxgi.lib")
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#endif
#endif

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

//SDL includes
#include <SDL\SDL.h>
#include <SDL\SDL_system.h>

//Engine includes
//defines
#include "Defines\TypeDefines.h"
#include "Defines\Constants.h"
#include "Defines\MathDefines.h"
#include "Defines\Errors.h"
#include "Defines\Helpers.h"
#include "Defines\PlatformDefines.h"
#include "Defines\Paths.h"

//math
#include "Math\Matrix.h"
#include "Math\Vec.h"
#include "Math\Quaternion.h"
#include "Math\MathHelperMethods.h"

#include "Helper\HelperMethods.h"

//memory includes
#include "Memory\MemoryManager.h"
#include "Memory\Allocator.h"

#include "Core\Count.h"
#include "Core\System\System.h"
#include "Core\Managers\EventHandler.h"

//settings
#include "Settings/DirectXSettings.h"
#include "Settings/EngineSettings.h"
#include "Settings/WindowSettings.h"

//helpers
#include "Debug/LogType.h"
#include "Debug/Debug.h"
#include "Helper/ReturnWrapper.h"
#include "Memory/Memory.h"

//containers
#include "Container/Vector.h"
