// Lucas de Souza Góes (C) 2020
#include "Colliseum.h"
#include "InputManager.h"
#include "Game.h"
#include "MainMenu.h"
#include "Battle.h"

using namespace std;

Colliseum::Colliseum()
{
	battlePtr = make_shared<Battle>(Battle());
}

void Colliseum::Update(Game* const gameRef)
{
	battlePtr->Update();
	if (battlePtr->IsBattleOver())
	{
		gameRef->End();
	}
}

void Colliseum::Draw(wchar_t* screen, const int screenHeight, const int screenWidth)
{
	battlePtr->Draw(screen, screenWidth, screenHeight);
}
