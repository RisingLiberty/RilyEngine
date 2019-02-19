#pragma once

namespace Graphics::Rendering
{
	class Renderer;
}

class Camera;
namespace Graphics::Context
{
class Context;
}

namespace Settings
{


struct WindowSettings
{
	WindowSettings() = default;
	WindowSettings(const int width, const int height, const std::string& title);
	~WindowSettings() = default;

#ifdef WINDOWS_PLATFORM
	bool UseDirectX = true;
#else
	bool UseDirectX = false;
#endif

	int Width;
	int Height;
	std::string Title;
	Graphics::Rendering::Renderer* pRenderer = nullptr;
	Camera* pCamera = nullptr;
	Graphics::Context::Context* pContext = nullptr;
};

}
