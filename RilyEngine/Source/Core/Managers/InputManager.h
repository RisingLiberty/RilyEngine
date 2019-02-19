#pragma once

#include "../../Helper/Singleton.h"

class InputManager : public Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();

	bool IsKeyDown(const char* key);
	bool IsMouseDown(int index);
	Math::Vec2 GetMouseMovement();

	//keyboard
	void KeyUp(const SDL_Event& event);
	void KeyDown(const SDL_Event& event);

	//mouse
	void MouseMotion(const SDL_Event& event);
	void MouseButtonUp(const SDL_Event& event);
	void MouseButtonDown(const SDL_Event& event);
	void MouseWheelMotion(const SDL_Event& event);

	//devices
	void JoystickMotion(const SDL_Event& event);
	void JoystickUp(const SDL_Event& event);
	void JoystickDown(const SDL_Event& event);

	void ControllerAxisMotion(const SDL_Event& event);
	void ControllerButtonUp(const SDL_Event& event);
	void ControllerButtonDown(const SDL_Event& event);
	void ControllerAdded(const SDL_Event& event);
	void ControllerRemoved(const SDL_Event& event);

	void NoEvent();

private:
	char TranslateKey(std::string& character) const;

	//key states holding possible key presses --> if true: key is pressed
	std::unordered_map<char, bool> m_KeyStates;
	std::unordered_map<char, bool> m_PrevKeyStates;

	Math::Vec2 m_LastMousePos;
	Math::Vec2 m_MousePos;

	std::unordered_map<char, bool> m_MouseButtonsStates;
};

