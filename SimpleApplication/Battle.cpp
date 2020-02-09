// Lucas de Souza Góes (C) 2020

#include "Battle.h"
#include "InputManager.h"
#include "Unit.h"


using namespace std;

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

void Battle::Update(chrono::milliseconds time)
{
	const auto timeBetweenActions = 1000ms;
	if (IsPlayingActions)
	{
		if (lastRecordedTime + timeBetweenActions < time)
		{
			lastRecordedTime = time;
			PlayActions();
		}
		
	}
	else {
		ChooseAction();
	}
}

void Battle::Draw(wchar_t* screen,const int screenWidth,const int screenHeight)
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
			DrawToScreen(screen, screenWidth, UIWidth + 8, optionsHeight, "> "s+options[i]);

		}
		else
		{
			DrawToScreen(screen, screenWidth, UIWidth + 10, optionsHeight, options[i]);
		}
		DrawToScreen(screen, screenWidth, UIWidth, optionsHeight+2,separatorLine);

	}

	int messageX = (actionMessage.size() / 2) - 20;
	DrawToScreen(screen, screenWidth, 10, 10, actionMessage);

	for (size_t i = 0; i < playerPartyPtr.size(); i++)
	{
		int xPos = 10 + 25 * i;
		// Drawing the player information
		DrawToScreen(screen, screenWidth, xPos, UIHeight + 2, "Name: " + playerPartyPtr[i]->getName());
		DrawToScreen(screen, screenWidth, xPos, UIHeight + 3, "-------------");
		DrawToScreen(screen, screenWidth, xPos, UIHeight + 4, playerPartyPtr[i]->getHealthUI());
	}
	
	
	const int enemyWidth = screenWidth * 0.2;
	// Drawing the enemy information
	for (size_t i = 0; i < enemies.size(); i++)
	{
		int xPos = enemyWidth + 25 * i;
		if (IsSelectingEnemy && enemySelectionIndex == i)
		{
			DrawToScreen(screen, screenWidth, xPos-2, 5, "> Name: " + enemies[i]->getName());
			DrawToScreen(screen, screenWidth, xPos, 6, "-------------");
			DrawToScreen(screen, screenWidth, xPos, 7, enemies[i]->getHealthUI());
		}
		else
		{
			DrawToScreen(screen, screenWidth, xPos, 5, "Name: " + enemies[i]->getName());
			DrawToScreen(screen, screenWidth, xPos, 6, "-------------");
			DrawToScreen(screen, screenWidth, xPos, 7, enemies[i]->getHealthUI());
		}
		
	}

}

bool Battle::IsBattleOver() const
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

void Battle::ChooseAction()
{
	if (fighters[fighterIndex].getFighter()->IsDead())
	{
		fighterIndex++;
	}
	else if (fighters[fighterIndex].getFighter()->getUnitType() == Unit::UnitType::Player)
	{
		
		if (IsSelectingAction)
		{
			SelectAction();
		}
		else if (IsSelectingEnemy)
		{
			SelectEnemies();
		}
	}
	else
	{
		int playerSelectionIndex = 0;
		while (playerPartyPtr[playerSelectionIndex]->IsDead())
		{
			playerSelectionIndex++;
		}
		fighters[fighterIndex].SetTurn(ActionType::Attack, playerPartyPtr[playerSelectionIndex]);
		fighterIndex++;
	}
	if (fighterIndex >= fighters.size())
	{
		fighterIndex = 0;
		IsPlayingActions = true;
		IsSelectingAction = false;
	}
}

void Battle::SelectAction()
{
	if (InputManager::GetKeyDown(KeyCode::ArrowDown))
	{
		selectedOptionIndex++;
		if (selectedOptionIndex >= options.size())
		{
			selectedOptionIndex = options.size() - 1;
		}
	}
	else if (InputManager::GetKeyDown(KeyCode::ArrowUp))
	{
		selectedOptionIndex--;
		if (selectedOptionIndex <= 0)
		{
			selectedOptionIndex = 0;
		}
	}
	else if (InputManager::GetKeyDown(KeyCode::Return))
	{
		switch (selectedOptionIndex)
		{
		case 0:// Attack
			IsSelectingAction = false;
			IsSelectingEnemy = true;
			break;
		case 1: // Defend
			IsSelectingAction = true;
			fighters[fighterIndex].SetTurn(ActionType::Defend);
			fighterIndex++;
			break;
		case 2: // Escape
			IsSelectingAction = true;
			fighters[fighterIndex].SetTurn(ActionType::Escape);
			fighterIndex++;
			//isBattleOver = true; TODO - End battle when escape comes up
			break;
		default:
			break;
		}
		selectedOptionIndex = 0;
	}
}

void Battle::SelectEnemies()
{
	if (InputManager::GetKeyDown(KeyCode::ArrowRight))
	{
		enemySelectionIndex++;
		if (enemySelectionIndex >= enemies.size())
		{
			enemySelectionIndex = enemies.size() - 1;
		}
	}
	else if (InputManager::GetKeyDown(KeyCode::ArrowLeft))
	{
		enemySelectionIndex--;
		if (enemySelectionIndex <= 0)
		{
			enemySelectionIndex = 0;
		}
	}
	else if (InputManager::GetKeyDown(KeyCode::Return))
	{
		if(!enemies[enemySelectionIndex]->IsDead())
		{
			IsSelectingAction = true;
			IsSelectingEnemy = false;
			fighters[fighterIndex].SetTurn(ActionType::Attack, enemies[enemySelectionIndex]);
			fighterIndex++;
			enemySelectionIndex = 0;
		}
	}
}

void Battle::PlayActions()
{
	if (IsAllDead(playerPartyPtr) || IsAllDead(enemies))
	{
		isBattleOver = true;
	}
	else
	{
		if (fighters[fighterIndex].getAction() == ActionType::Escape)
		{
			isBattleOver = true;
		}
		if (!fighters[fighterIndex].getFighter()->IsDead())
		{
			actionMessage = fighters[fighterIndex].DoAction();
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

bool Battle::IsAllDead(std::vector<shared_ptr<Unit>> collection)
{
	for (const auto& unit : collection)
	{
		if (!unit->IsDead())
		{
			return false;
		}
	}
	return true;
}
