#include <stdafx.h>

#include <Core\Engine.h>
#include <Core\GameBase.h>

#include "RilyGame.h"


#undef main

int main()
{
	Core::GameBase* pGame = new RilyGame();
	pGame->Start();
	delete pGame;
}