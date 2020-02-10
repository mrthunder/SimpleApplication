//Lucas de Souza Góes (c) 2020

// Includes
#include "Fighter.h"

// Using(s)
using std::literals::string_literals::operator""s;

Fighter::Fighter(shared_ptr<Unit> unit)
	: fighter(unit)
{
}


void Fighter::setTurn(ActionType action, shared_ptr<Unit> unitTarget)
{
	fighter->resetTurn();
	turnAction = action;
	target = unitTarget;
}

string Fighter::doAction()
{
	switch (turnAction)
	{
	case ActionType::None:
		return fighter->getName() + " did nothing."s;
	case ActionType::Attack:
		if (target)
		{
			target->damage(fighter->getAttackDamage());
			return fighter->getName() + " attacked "s + target->getName();
		}
		else
		{
			return "Missing target!!"s;
		}
	case ActionType::Defend:
		fighter->defend();
		return fighter->getName() + " is defending."s;
	case ActionType::Escape:
		return fighter->getName() + " escaped."s;
	default:
		return "Something went wrong."s;
	}
	
}

const shared_ptr<Unit> Fighter::getFighter() const
{
	return fighter;
}

ActionType Fighter::getAction() const
{
	return turnAction;
}
