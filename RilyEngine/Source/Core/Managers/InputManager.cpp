#include "stdafx.h"

#include "InputManager.h"

#include "Core/System/Window.h"

#include "Defines/Keys.h"
#include "Defines/KeyHashes.h"

#include "Settings/EngineSettings.h"

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

bool InputManager::IsKeyDown(const char* key)
{
	return m_KeyStates[*key];
}

bool InputManager::IsMouseDown(int index)
{
	return m_MouseButtonsStates[index];
}

Math::Vec2 InputManager::GetMouseMovement()
{
	//TODO: Get mouse position at start
	static bool isFirst = true;

	Math::Vec2 motion = UnitVec2;

	if (isFirst)
		isFirst = false;
	
	else
	{
		motion = m_MousePos - m_LastMousePos;
		m_LastMousePos = m_MousePos;
	}

	return motion;
}

void InputManager::KeyUp(const SDL_Event & event)
{
	std::string character = SDL_GetKeyName(event.key.keysym.sym);
	char c = TranslateKey(character);
	m_KeyStates[c] = false;
}

void InputManager::KeyDown(const SDL_Event & event)
{
	std::string character = SDL_GetKeyName(event.key.keysym.sym);
	char c = TranslateKey(character);
	m_KeyStates[c] = true;
}

void InputManager::MouseMotion(const SDL_Event & event)
{
	m_LastMousePos = m_MousePos;
	m_MousePos.x = (float)event.motion.x;
	m_MousePos.y = (float)event.motion.y;
}

void InputManager::MouseButtonUp(const SDL_Event & event)
{
	m_MouseButtonsStates[event.button.button] = false;
}

void InputManager::MouseButtonDown(const SDL_Event & event)
{
	m_MouseButtonsStates[event.button.button] = true;
}

void InputManager::MouseWheelMotion(const SDL_Event & event)
{
}

void InputManager::JoystickMotion(const SDL_Event & event)
{
}

void InputManager::JoystickUp(const SDL_Event & event)
{
}

void InputManager::JoystickDown(const SDL_Event & event)
{
}

void InputManager::ControllerAxisMotion(const SDL_Event & event)
{
}

void InputManager::ControllerButtonUp(const SDL_Event & event)
{
}

void InputManager::ControllerButtonDown(const SDL_Event & event)
{
}

void InputManager::ControllerAdded(const SDL_Event & event)
{
}

void InputManager::ControllerRemoved(const SDL_Event & event)
{
}

char InputManager::TranslateKey(std::string& character) const
{
	if (character.empty())
		assert(false);

	if (character.length() == 1)
		return character.front();

	std::transform(character.begin(), character.end(), character.begin(), tolower);

	UINT64 hashStr = hash(character.c_str());

	switch (hashStr)
	{
	case HASH_LEFT_SHIFT:
		return KEY_LEFT_SHIFT;

	case HASH_RIGHT_SHIFT:
		return KEY_RIGHT_SHIFT;

	case HASH_LEFT_CTRL:
		return KEY_LEFT_CTRL;

	case HASH_RIGHT_CTRL:
		return KEY_RIGHT_CTRL;

	case HASH_LEFT_ALT:
		return KEY_LEFT_ALT;

	case HASH_RIGHT_ALT:
		return KEY_RIGHT_ALT;

	case HASH_CAPS_LOCK:
		return KEY_CAPS_LOCK;

	case HASH_TAB:
		return KEY_TAB;

	case HASH_RETURN:
		return KEY_RETURN;

	case HASH_UP_ARROW:
		return KEY_UP_ARROW;

	case HASH_DOWN_ARROW:
		return KEY_DOWN_ARROW;

	case HASH_LEFT_ARROW:
		return KEY_LEFT_ARROW;

	case HASH_RIGHT_ARROW:
		return KEY_RIGHT_ARROW;

	case HASH_EQUAL:
		return KEY_EQUAL;

	case HASH_BACKSPACE:
		return KEY_BACKSPACE;

	case HASH_ESC:
		return KEY_ESC;

	case HASH_SPACE:
		return KEY_SPACE;

	case HASH_PAGE_UP:
		return KEY_PAGE_UP;

	case HASH_PAGE_DOWN:
		return KEY_PAGE_DOWN;

	case HASH_END:
		return KEY_END;

	case HASH_HOME:
		return KEY_HOME;

	case HASH_INSERT:
		return KEY_INSERT;

	case HASH_DELETE:
		return KEY_DELETE;

	case HASH_NUMPAD_0:
		return KEY_NUMPAD_0;

	case HASH_NUMPAD_1:
		return KEY_NUMPAD_1;

	case HASH_NUMPAD_2:
		return KEY_NUMPAD_2;

	case HASH_NUMPAD_3:
		return KEY_NUMPAD_3;

	case HASH_NUMPAD_4:
		return KEY_NUMPAD_4;

	case HASH_NUMPAD_5:
		return KEY_NUMPAD_5;

	case HASH_NUMPAD_6:
		return KEY_NUMPAD_6;

	case HASH_NUMPAD_7:
		return KEY_NUMPAD_7;

	case HASH_NUMPAD_8:
		return KEY_NUMPAD_8;

	case HASH_NUMPAD_9:
		return KEY_NUMPAD_9;

	case HAHS_KEYPAD_MULTIPLY:
		return KEY_KEYPAD_MULTIPLY;

	case HASH_KEYPAD_ADD:
		return KEY_KEYPAD_ADD;

	case HASH_KEYPAD_MINUS:
		return KEY_KEYPAD_MINUS;

	case HASH_KEYPAD_DIVIDE:
		return KEY_KEYPAD_DIVIDE;

	case HASH_KEYPAD_ENTER:
		return KEY_KEYPAD_ENTER;

	case HASH_KEYPAD_DOT:
		return KEY_KEYPAD_DOT;

	case HASH_F1:
		return KEY_F1;

	case HASH_F2:
		return KEY_F2;

	case HASH_F3:
		return KEY_F3;

	case HASH_F4:
		return KEY_F4;

	case HASH_F5:
		return KEY_F5;

	case HASH_F6:
		return KEY_F6;

	case HASH_F7:
		return KEY_F7;

	case HASH_F8:
		return KEY_F8;

	case HASH_F9:
		return KEY_F9;

	case HASH_F10:
		return KEY_F10;

	case HASH_F11:
		return KEY_F11;

	case HASH_F12:
		return KEY_F12;

	case HASH_NUM_LOCK:
		return KEY_NUM_LOCK;

	case WINDOWS_LEFT:
		return KEY_WIN_LEFT;

	default:
		Debug::Log(Debug::LogType::WARNING, character, " not correct");
		std::cin.get();
	}

	return NULL;
}

void InputManager::NoEvent()
{
	m_MousePos = m_LastMousePos;
}