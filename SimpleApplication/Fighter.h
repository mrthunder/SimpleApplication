//Lucas de Souza Góes (c) 2020
#pragma once

// Includes
#include <memory>
#include <string>
#include "Unit.h"

// Using(s)
using std::shared_ptr;
using std::string;

// Battle actions
enum class ActionType {
	None,
	Attack,
	Defend,
	Escape,
};

class Fighter
{
public:
	Fighter(shared_ptr<Unit> unit); // Ctor
	void setTurn(ActionType action, shared_ptr<Unit> unitTarget = nullptr); // Set the turn action
	string doAction(); // Play the turn action, and returns a message to show on the screen
	const shared_ptr<Unit> getFighter() const; // Get the unit assigned as a fighter
	ActionType getAction() const; // Get the action set for the turn
private:
	shared_ptr<Unit> target = nullptr; // This fighter's target in case of attack
	ActionType turnAction = ActionType::None; // The turn action
	shared_ptr<Unit> fighter; // This fighter
	
};

