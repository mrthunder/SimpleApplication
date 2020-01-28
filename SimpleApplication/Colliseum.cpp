// Lucas de Souza Góes (C) 2020
#include "Colliseum.h"
#include "InputManager.h"
#include "Game.h"
#include "MainMenu.h"
#include "Battle.h"
#include "Unit.h"

using namespace std;

Colliseum::Colliseum()
{
	playerPtr = make_shared<Unit>("Player"s,100,20,10,3);
	enemyPtr = new Unit();
	battlePtr = make_shared<Battle>(playerPtr,enemyPtr);
}

Colliseum::~Colliseum()
{
	delete enemyPtr;
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

void Colliseum::GenerateNewEnemy()
{
	delete enemyPtr;
	enemyPtr = nullptr;
	enemyPtr = new Unit();
}
