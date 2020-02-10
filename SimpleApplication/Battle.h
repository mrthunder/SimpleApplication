// Lucas de Souza Góes (C) 2020
#pragma once

// Includes
#include <string>
#include <vector>
#include <memory>
#include "Fighter.h"
#include <chrono>

//Using(s)
using std::vector;
using std::shared_ptr;
using std::chrono::milliseconds;
using std::string;

// Forward Declaration
class Unit;

class Battle
{
public:
	Battle(vector<shared_ptr<Unit>> party); // Ctor
	void update(milliseconds time); // This method executes every frame
	void draw(wchar_t* screen,const int screenWidth,const int screenHeight); // This method executes every frame
	bool getIsBattleOver() const; // Returns the state of the battle
private:
	inline void drawToScreen(wchar_t* screen, const int screenWidth, int posX, int posY, string content)
	{
		for (size_t i = 0; i < content.length(); i++)
		{
			screen[posY * screenWidth + (posX + i)] = content[i];
		}

	}
	void makeEnemies(); // Make random enemies for the battle
	void chooseAction(); // Prompt the player to chose the actions for the characters
	void selectAction(); // Action selection controls
	void selectEnemies(); // Enemy selection controls
	void playActions(); // Play the actions selected by each unit in order of the fastest.
	                     // (There is a small delay between actions)
	bool isAllDead(vector<shared_ptr<Unit>> collection); // Check if any group have every member dead.
	
private:
	vector<string> options{"Attack", "Defend", "Escape" }; // Action options
	int selectedOptionIndex = 0; // Actions index
	bool isBattleOver = false; // When the battle is over this is true
	vector<shared_ptr<Unit>> playerPartyPtr; // The character with type player
	vector<shared_ptr<Unit>> enemies{}; // The enemies
	vector<Fighter> fighters; // All the units sorted by the fastest.
	int fighterIndex = 0; // This track which character select their action or play their action
	int enemySelectionIndex = 0; // When selecting which enemy to attack 
	                              // this is the index that helps display on the screen 
	bool IsSelectingEnemy = false; // If this is true, then the greater sign (>) will show by the enemy name
	bool IsSelectingAction = true; // If this is true, then the greater sign (>) will show by the action name 
	bool IsPlayingActions = false; // If this is true the playActions function is running otherwise the chooseAction is running
	milliseconds lastRecordedTime; // This helps delaying the actions to show the message to the screen
	string actionMessage = ""; // After each action a message will be display on the screen describing what happened
};

