// Lucas de Souza Góes (C) 2020
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Fighter.h"
#include <chrono>
class Unit;

class Battle
{
public:
	Battle(std::vector<std::shared_ptr<Unit>> party);
	void Update(std::chrono::milliseconds time);
	void Draw(wchar_t* screen,const int screenWidth,const int screenHeight);
	bool IsBattleOver() const;
private:
	inline void DrawToScreen(wchar_t* screen, const int screenWidth, int posX, int posY, std::string content)
	{
		for (size_t i = 0; i < content.length(); i++)
		{
			screen[posY * screenWidth + (posX + i)] = content[i];
		}

	}
	void makeEnemies();
	void ChooseAction();
	void SelectAction(); // Action selection controls
	void SelectEnemies();
	void PlayActions();
	bool IsAllDead(std::vector<std::shared_ptr<Unit>> collection);
	
private:
	std::vector<std::string> options{"Attack", "Defend", "Escape" };
	int selectedOptionIndex = 0;
	bool isBattleOver = false;
	std::vector<std::shared_ptr<Unit>> playerPartyPtr;
	std::vector<std::shared_ptr<Unit>> enemies{};
	std::vector<Fighter> fighters;
	int fighterIndex = 0;
	int enemySelectionIndex = 0;
	bool IsSelectingEnemy = false;
	bool IsSelectingAction = true;
	bool IsPlayingActions = false;
	std::chrono::milliseconds lastRecordedTime;
	std::string actionMessage = "";
};

