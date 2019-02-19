#pragma once

class Renderer;

class Window : public Count<Window>, public System
{
public:
	Window(uint_t width = WINDOW_WIDTH, uint_t height = WINDOW_HEIGHT, const std::string& title = WINDOW_TITLE);
	Window(const Window& window) = delete;
	Window(const Window&& window) = delete;
	Window operator=(const Window& window) = delete;
	Window operator=(const Window&& window) = delete;

	~Window();

	int Initialize() override;
	int Update() override;
	
	void Clear();
	void Resize(const int width, const int height);
	void Close();

	bool IsClosed() const { return m_IsClosed; }

	void SetRenderer(Graphics::Rendering::Renderer* pRenderer) { m_Settings.pRenderer = pRenderer; }
	Graphics::Rendering::Renderer* GetRenderer() const { return m_Settings.pRenderer; }

	void SetCamera(Camera* pCamera) { m_Settings.pCamera = pCamera; }
	Camera* GetCamera() const { return m_Settings.pCamera; }

	void SetWidth(uint_t width) { m_Settings.Width = width; }
	uint_t GetWidth() const { return m_Settings.Width; }

	void SetHeight(uint_t height) { m_Settings.Height = height; }
	uint_t GetHeight() const { return m_Settings.Height; }

	void IsFullScreen(bool isFullScreen) { m_IsFullScreen = isFullScreen; }
	bool IsFullScreen() const { return m_IsFullScreen; }

	void SetSdlHandle(SDL_Window* handle) { m_pSdlHandle = handle; }
	SDL_Window* GetSdlHandle() const { return m_pSdlHandle; }

	Graphics::Context::Context* GetContext() const { return m_Settings.pContext; }
	void SetContext(Graphics::Context::Context* pContext) { m_Settings.pContext = pContext; }

	//for windows platform
#if defined WINDOWS_PLATFORM
	void SetHandle(HWND handle) { m_Handle = handle; }
	HWND GetHandle() const { return m_Handle; }
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

private:

#if defined WINDOWS_PLATFORM
	WNDCLASS CreateWndClass();
	int SetupWindow();
#endif

private:
	SDL_Window* m_pSdlHandle = nullptr;
	Settings::WindowSettings m_Settings;
	bool m_IsFullScreen = false;
	bool m_IsActive = false;
	bool m_IsClosed = false;

#ifdef WINDOWS_PLATFORM
	HWND m_Handle = NULL;
	HINSTANCE m_HInstance = NULL;
#endif

};

