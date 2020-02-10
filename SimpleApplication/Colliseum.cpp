// Lucas de Souza Góes (C) 2020
 
// Includes
#include "Colliseum.h"
#include "InputManager.h"
#include "Game.h"
#include "MainMenu.h"
#include "Battle.h"
#include "Unit.h"

// Using(s)
using std::literals::string_literals::operator""s;


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

void Colliseum::update(Game* const gameRef, milliseconds time)
{
	battlePtr->update(time);
	if (battlePtr->getIsBattleOver())
	{
		gameRef->end();
	}
}

void Colliseum::draw(wchar_t* screen, const int screenHeight, const int screenWidth)
{
	battlePtr->draw(screen, screenWidth, screenHeight);
}

