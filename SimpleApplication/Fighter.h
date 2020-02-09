#pragma once
#include <memory>
#include <string>
#include "Unit.h"


enum class ActionType {
	None,
	Attack,
	Defend,
	Escape,
};

class Fighter
{
public:
	Fighter(std::shared_ptr<Unit> unit);
	void SetTurn(ActionType action, std::shared_ptr<Unit> unitTarget = nullptr);
	std::string DoAction();
	const std::shared_ptr<Unit> getFighter() const;
	ActionType getAction() const;
private:
	std::shared_ptr<Unit> target = nullptr;
	ActionType turnAction = ActionType::None;
	std::shared_ptr<Unit> fighter;
	
};

