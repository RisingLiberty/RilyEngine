#include "stdafx.h"

#include "Window.h"

#include "Clock.h"

#include "Core/Managers/SystemManager.h"

#include "Graphics/Context/OpenGLContext.h"
#include "Graphics/Rendering/Renderer.h"
#include "Graphics/Camera.h"


Window::Window(uint_t width, uint_t height, const std::string& title):
	System(SystemType::WINDOW),
	m_Settings(Settings::WindowSettings(width, height, title))
{
	m_Settings.pRenderer = SystemManager::GetInstance()->GetRenderer();

#if defined WINDOWS_PLATFORM
	if (!RegisterClass(&CreateWndClass()))
	{
		int error = GetLastError();
		PUSH_ERROR_ID("failed to registed window class", error);
	}

	uint_t result = SetupWindow();
	if (result != OK) return result;
	
	ShowWindow(m_Handle, SW_SHOW);
	SetForegroundWindow(m_Handle);
	SetFocus(m_Handle);

	m_pSdlHandle = SDL_CreateWindowFrom(m_Handle);

	if (!m_pSdlHandle)
	{
		PUSH_ERROR(SDL_GetError());
		return FAILED_TO_CREATE_WINDOW_SDL;
	}

#else
	//Needs to be called before actual window creation
	ColorBufferDesc colorBufferDesc = m_Settings.pRenderer->GetColorBufferDesc();
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, colorBufferDesc.RedChannelSize);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, colorBufferDesc.GreenChannelSize);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, colorBufferDesc.BlueChannelSize);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, colorBufferDesc.AlphaChannelSize);

	DepthBufferDesc depthBufferDesc = m_Settings.pRenderer->GetDepthBufferDesc();
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depthBufferDesc.DepthChannelSize);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, depthBufferDesc.StencilChannelSize);

#endif
	m_pSdlHandle = SDL_CreateWindow(m_Settings.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Settings.Width, m_Settings.Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	m_Settings.pContext = new Graphics::Context::OpenGLContext(this);
	m_Settings.pContext->Initialize();

	m_IsActive = true;
}


Window::~Window()
{
	SDL_DestroyWindow(m_pSdlHandle);
	SAFE_DELETE(m_Settings.pCamera);
	SAFE_DELETE(m_Settings.pContext);
}

int Window::Initialize()
{
	System::Initialize();
	m_Settings.pCamera = new Camera(Math::Vec2((float)m_Settings.Width, (float)m_Settings.Height));
	m_Settings.pCamera->Initialize();
	m_Settings.pCamera->Translate(Math::Vec3(0, 0, 2));

	return OK;
}

int Window::Update()
{
	m_Settings.pCamera->Update(SystemManager::GetInstance()->GetClock()->GetDeltaTime());
	return OK;
}

void Window::Clear()
{
	m_Settings.pRenderer->ClearScreen();
}

void Window::Resize(const int width, const int height)
{
	SetWidth(width);
	SetHeight(height);

	SDL_SetWindowSize(m_pSdlHandle, width, height);
	m_Settings.pCamera->SetAspectRatio(Math::Vec2((float)width, (float)height));

}

void Window::Close()
{
	m_IsClosed = true;
}

#if defined WINDOWS_PLATFORM
WNDCLASS Window::CreateWndClass()
{
	if (m_Settings.Title.length() > 256)
	{
		PUSH_ERROR("failed to create window class, title too long");
		return {};
	}

	WNDCLASS wndClass;
	wndClass = {};

	wndClass.style = CS_HREDRAW | CS_VREDRAW;			//redraw on x and y axis when window is scaled.
	wndClass.lpfnWndProc = WndProc;						//static window procedure.
	wndClass.hInstance = m_HInstance;					//hinstance of this object.
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//load standard application icon.
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		//load standard arrow cursor.
	wndClass.lpszClassName = m_Settings.Title.c_str();

	return wndClass;
}

int Window::SetupWindow()
{
	RECT screen;
	HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &screen);
	int x = (screen.right / 2) - (m_Settings.Width / 2);
	int y = (screen.bottom / 2) - (m_Settings.Height / 2);

	m_Handle = CreateWindowA(
		m_Settings.Title.c_str(),
		m_Settings.Title.c_str(),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		x,
		y,
		m_Settings.Width,
		m_Settings.Height,
		NULL,
		NULL,
		m_HInstance,
		this
	);

	if (!m_Handle)
	{
		int error = GetLastError();
		PUSH_WARNING_ID("Failed to setup window", error);
		return FAILED_TO_SETUP_WINDOW;
	}
	return OK;
}

LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CREATE)
	{
		CREATESTRUCT* pCs = reinterpret_cast<CREATESTRUCT*>(lParam);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG>(pCs->lpCreateParams));
	}
	else
	{
		Window* pWindow = (Window*)(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		if (pWindow)
			return pWindow->HandleEvent(hwnd, msg, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT Window::HandleEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATE:
		if (HIWORD(wParam))
			m_IsActive = true;
		else 
			m_IsActive = false;
	
		break;
	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case SC_MAXIMIZE:
			m_IsFullScreen = true;
			break;
		case SC_MINIMIZE:
			m_IsActive = false;	
			break;
		}
		break;
	}
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		Resize(LOWORD(lParam), HIWORD(lParam));
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

#endif