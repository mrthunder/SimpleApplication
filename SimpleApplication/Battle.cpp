// Lucas de Souza Góes (C) 2020

// Includes
#include "Battle.h"
#include "InputManager.h"
#include "Unit.h"

// Using(s)
using std::literals::chrono_literals::operator""ms;
using std::literals::string_literals::operator""s;
using std::make_shared;

Battle::Battle(vector<shared_ptr<Unit>> party)
	: playerPartyPtr(party)
{
	makeEnemies();
	size_t fightersSize = playerPartyPtr.size() + enemies.size();
	for (size_t i = 0; i < fightersSize; i++)
	{
		if (i < playerPartyPtr.size())
		{
			fighters.emplace_back(playerPartyPtr[i]);
		}
		else {
			fighters.emplace_back(enemies[i-playerPartyPtr.size()]);
		}
		
	}
	lastRecordedTime = 0ms;
}

void Battle::update(milliseconds time)
{
	const auto timeBetweenActions = 1000ms;
	if (IsPlayingActions)
	{
		if (lastRecordedTime + timeBetweenActions < time)
		{
			lastRecordedTime = time;
			playActions();
		}
		
	}
	else {
		chooseAction();
	}
}

void Battle::draw(wchar_t* screen,const int screenWidth,const int screenHeight)
{
	const char square = '#';
	const int UIWidth = 90;
	const int UIHeight = 27;
	
	// Drawing the edge
	for (int i =0; i < screenWidth; i++)
	{
		for (int j = 0; j < screenHeight; j++)
		{
			int index = j * screenWidth + i;
			//edge
			
			if (j == 0 || j == screenHeight - 1||j==UIHeight 
				|| i == 0 || i == screenWidth - 1 
				||(j > UIHeight&& i == UIWidth))
			{
				screen[index] = square;
			}
		}
	}
	int lineLength = screenWidth - UIWidth;
	const string separatorLine = string(lineLength, '#');
	// Drawing the option menu
	for (size_t i = 0; i < options.size();i++)
	{
		int optionsHeight = UIHeight + 2 *(i*2+1);
		if (IsSelectingAction && selectedOptionIndex == i)
		{
			drawToScreen(screen, screenWidth, UIWidth + 8, optionsHeight, "> "s+options[i]);

		}
		else
		{
			drawToScreen(screen, screenWidth, UIWidth + 10, optionsHeight, options[i]);
		}
		drawToScreen(screen, screenWidth, UIWidth, optionsHeight+2,separatorLine);

	}

	int messageX = (actionMessage.size() / 2) - 20;
	drawToScreen(screen, screenWidth, 10, 10, actionMessage);

	for (size_t i = 0; i < playerPartyPtr.size(); i++)
	{
		int xPos = 10 + 25 * i;
		// Drawing the player information
		drawToScreen(screen, screenWidth, xPos, UIHeight + 2, "Name: " + playerPartyPtr[i]->getName());
		drawToScreen(screen, screenWidth, xPos, UIHeight + 3, "-------------");
		drawToScreen(screen, screenWidth, xPos, UIHeight + 4, playerPartyPtr[i]->getHealthUI());
	}
	
	
	const int enemyWidth = screenWidth * 0.2;
	// Drawing the enemy information
	for (size_t i = 0; i < enemies.size(); i++)
	{
		int xPos = enemyWidth + 25 * i;
		if (IsSelectingEnemy && enemySelectionIndex == i)
		{
			drawToScreen(screen, screenWidth, xPos-2, 5, "> Name: " + enemies[i]->getName());
			drawToScreen(screen, screenWidth, xPos, 6, "-------------");
			drawToScreen(screen, screenWidth, xPos, 7, enemies[i]->getHealthUI());
		}
		else
		{
			drawToScreen(screen, screenWidth, xPos, 5, "Name: " + enemies[i]->getName());
			drawToScreen(screen, screenWidth, xPos, 6, "-------------");
			drawToScreen(screen, screenWidth, xPos, 7, enemies[i]->getHealthUI());
		}
		
	}

}

bool Battle::getIsBattleOver() const
{
	return isBattleOver;
}

void Battle::makeEnemies()
{
	size_t randomEnemyCount = (rand() % 3)+1;
	for (size_t i = 0; i < randomEnemyCount; i++)
	{
		enemies.push_back(make_shared<Unit>());
	}
}

void Battle::chooseAction()
{
	if (fighters[fighterIndex].getFighter()->isUnitDead())
	{
		fighterIndex++;
	}
	else if (fighters[fighterIndex].getFighter()->getUnitType() == Unit::UnitType::Player)
	{
		
		if (IsSelectingAction)
		{
			selectAction();
		}
		else if (IsSelectingEnemy)
		{
			selectEnemies();
		}
	}
	else
	{
		int playerSelectionIndex = 0;
		while (playerPartyPtr[playerSelectionIndex]->isUnitDead())
		{
			playerSelectionIndex++;
		}
		fighters[fighterIndex].setTurn(ActionType::Attack, playerPartyPtr[playerSelectionIndex]);
		fighterIndex++;
	}
	if (fighterIndex >= fighters.size())
	{
		fighterIndex = 0;
		IsPlayingActions = true;
		IsSelectingAction = false;
	}
}

void Battle::selectAction()
{
	if (InputManager::getKeyDown(KeyCode::ArrowDown))
	{
		selectedOptionIndex++;
		if (selectedOptionIndex >= options.size())
		{
			selectedOptionIndex = options.size() - 1;
		}
	}
	else if (InputManager::getKeyDown(KeyCode::ArrowUp))
	{
		selectedOptionIndex--;
		if (selectedOptionIndex <= 0)
		{
			selectedOptionIndex = 0;
		}
	}
	else if (InputManager::getKeyDown(KeyCode::Return))
	{
		switch (selectedOptionIndex)
		{
		case 0:// Attack
			IsSelectingAction = false;
			IsSelectingEnemy = true;
			break;
		case 1: // Defend
			IsSelectingAction = true;
			fighters[fighterIndex].setTurn(ActionType::Defend);
			fighterIndex++;
			break;
		case 2: // Escape
			IsSelectingAction = true;
			fighters[fighterIndex].setTurn(ActionType::Escape);
			fighterIndex++;
			break;
		default:
			break;
		}
		selectedOptionIndex = 0;
	}
}

void Battle::selectEnemies()
{
	if (InputManager::getKeyDown(KeyCode::ArrowRight))
	{
		enemySelectionIndex++;
		if (enemySelectionIndex >= enemies.size())
		{
			enemySelectionIndex = enemies.size() - 1;
		}
	}
	else if (InputManager::getKeyDown(KeyCode::ArrowLeft))
	{
		enemySelectionIndex--;
		if (enemySelectionIndex <= 0)
		{
			enemySelectionIndex = 0;
		}
	}
	else if (InputManager::getKeyDown(KeyCode::Return))
	{
		if(!enemies[enemySelectionIndex]->isUnitDead())
		{
			IsSelectingAction = true;
			IsSelectingEnemy = false;
			fighters[fighterIndex].setTurn(ActionType::Attack, enemies[enemySelectionIndex]);
			fighterIndex++;
			enemySelectionIndex = 0;
		}
	}
}

void Battle::playActions()
{
	if (isAllDead(playerPartyPtr) || isAllDead(enemies))
	{
		isBattleOver = true;
	}
	else
	{
		if (fighters[fighterIndex].getAction() == ActionType::Escape)
		{
			isBattleOver = true;
		}
		if (!fighters[fighterIndex].getFighter()->isUnitDead())
		{
			actionMessage = fighters[fighterIndex].doAction();
		}
		fighterIndex++;
		if (fighterIndex >= fighters.size())
		{
			IsPlayingActions = false;
			fighterIndex = 0;
			IsSelectingAction = true;
		}
	}

	
}

bool Battle::isAllDead(std::vector<shared_ptr<Unit>> collection)
{
	for (const auto& unit : collection)
	{
		if (!unit->isUnitDead())
		{
			return false;
		}
	}
	return true;
}
