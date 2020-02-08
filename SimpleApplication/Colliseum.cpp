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
	playerParty.push_back(make_shared<Unit>("Protagonist"s, 100, 20, 10, 3, Unit::UnitType::Player));
	playerParty.push_back(make_shared<Unit>("Sword Character"s, 100, 20, 10, 3, Unit::UnitType::Player));
	playerParty.push_back(make_shared<Unit>("Other Character"s, 100, 20, 10, 3, Unit::UnitType::Player));
	battlePtr = make_shared<Battle>(playerParty);
}

Colliseum::~Colliseum()
{
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

