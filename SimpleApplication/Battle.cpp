// Lucas de Souza Góes (C) 2020

#include "Battle.h"
#include "InputManager.h"
#include "Unit.h"

using namespace std;

Battle::Battle(std::shared_ptr<Unit> player, Unit* enemy)
	: playerPtr(player), enemyPtr(enemy)
{
}

void Battle::Update()
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
		if (selectedOptionIndex <=0)
		{
			selectedOptionIndex = 0;
		}
	}
	else if (InputManager::GetKeyDown(KeyCode::Return))
	{
		switch (selectedOptionIndex)
		{
		case 0:// Attack
			break;
		case 1: // Defend
			break;
		case 2: // Escape
			isBattleOver = true;
			break;
		default:
			break;
		}
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
		if (selectedOptionIndex == i)
		{
			DrawToScreen(screen, screenWidth, UIWidth + 8, optionsHeight, "> "s+options[i]);

		}
		else
		{
			DrawToScreen(screen, screenWidth, UIWidth + 10, optionsHeight, options[i]);
		}
		DrawToScreen(screen, screenWidth, UIWidth, optionsHeight+2,separatorLine);

	}
	// Drawing the player information
	DrawToScreen(screen, screenWidth, 10, UIHeight + 2, "Name: "+playerPtr->getName());
	DrawToScreen(screen, screenWidth, 10, UIHeight + 3, "-------------");
	DrawToScreen(screen, screenWidth, 10, UIHeight + 4, playerPtr->getHealthUI());

	// Drawing the enemy information
	if (enemyPtr != nullptr)
	{
		const int enemyWidth = screenWidth * 0.7;
		DrawToScreen(screen, screenWidth,enemyWidth , 5, "Name: " + enemyPtr->getName());
		DrawToScreen(screen, screenWidth, enemyWidth, 6, "-------------");
		DrawToScreen(screen, screenWidth, enemyWidth, 7, enemyPtr->getHealthUI());
	}

}

bool Battle::IsBattleOver() const
{
	return isBattleOver;
}
