#include "stdafx.h"

#include "EventHandler.h"

#include "InputManager.h"
#include "SystemManager.h"

#include "Core/System/Window.h"

int EventHandler::Update()
{
	int result = OK;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		result = this->ProcessEvent(event);
		if (result != OK)
			return result;
	}
	return result;
}

int EventHandler::ProcessEvent(const SDL_Event& event)
{
	switch (event.type)
	{
//application events
	case SDL_QUIT:						//application is quiting
		return QUIT;
		break;

//window events
	case SDL_WINDOWEVENT:				//window state change
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			SystemManager::GetInstance()->GetWindow()->Resize(event.window.data1, event.window.data2);
			break;
		case SDL_WINDOWEVENT_CLOSE:
			SystemManager::GetInstance()->GetWindow()->Close();
			break;
		default:
			break;
		}
		InputManager::GetInstance()->NoEvent();
		break;
	case SDL_SYSWMEVENT:				//system specific event
		break;

//key board events
	case SDL_KEYDOWN:					//key pressed
		InputManager::GetInstance()->KeyDown(event);
		break;
	case SDL_KEYUP:						//key released
		InputManager::GetInstance()->KeyUp(event);
		break;

//mouse events
	case SDL_MOUSEMOTION:				//mouse has moved
		InputManager::GetInstance()->MouseMotion(event);
		break;
	case SDL_MOUSEBUTTONDOWN:			//mouse button is pressed
		InputManager::GetInstance()->MouseButtonDown(event);
		break;
	case SDL_MOUSEBUTTONUP:				//mpouse button is released
		InputManager::GetInstance()->MouseButtonUp(event);
		break;
	case SDL_MOUSEWHEEL:				//mouse wheel motion
		break;

//external device events
//joystick
	case SDL_JOYAXISMOTION:				//joy stick motion
		break;
	case SDL_JOYBUTTONDOWN:				//joy stick pressed
		break;
	case SDL_JOYBUTTONUP:				//joy stick released
		break;

//controller
	case SDL_CONTROLLERAXISMOTION:		//controller axis motion
		break;
	case SDL_CONTROLLERBUTTONDOWN:		//controller button pressed
		break;
	case SDL_CONTROLLERBUTTONUP:		//controller button released
		break;
	case SDL_CONTROLLERDEVICEADDED:		//controller added
		break;
	case SDL_CONTROLLERDEVICEREMOVED:	//controller removed
		break;

//other events
	case SDL_DROPTEXT:					//text/plain drag-and-drop event
		break;
	case SDL_USEREVENT:					//user specified event
		break;
	default:
		InputManager::GetInstance()->NoEvent();
		break;
	}
	return OK;
}