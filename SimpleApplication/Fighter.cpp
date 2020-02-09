#include "Fighter.h"

using std::string;
using std::shared_ptr;


Fighter::Fighter(shared_ptr<Unit> unit)
	: fighter(unit)
{
}



void Fighter::SetTurn(ActionType action, shared_ptr<Unit> unitTarget)
{
	fighter->ResetTurn();
	turnAction = action;
	target = unitTarget;
}

string Fighter::DoAction()
{
	switch (turnAction)
	{
	case ActionType::None:
		return fighter->getName() + " did nothing.";
	case ActionType::Attack:
		if (target)
		{
			target->Damage(fighter->getAttackDamage());
			return fighter->getName() + " attacked " + target->getName();
		}
		else
		{
			return "Missing target!!";
		}
	case ActionType::Defend:
		fighter->Defend();
		return fighter->getName() + " is defending.";
	case ActionType::Escape:
		return fighter->getName() + " escaped.";
	default:
		return "Something went wrong.";
	}
	
}

const std::shared_ptr<Unit> Fighter::getFighter() const
{
	return fighter;
}

ActionType Fighter::getAction() const
{
	return turnAction;
}
