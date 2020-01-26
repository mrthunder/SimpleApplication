// Lucas de Souza Góes (C) 2020

#include "Battle.h"
#include "InputManager.h"

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

void Battle::Draw(wchar_t* screen, int screenWidth, int screenHeight)
{
	const char square = '#';
	const int UIWidth = 90;
	const int UIHeight = 27;
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


}

bool Battle::IsBattleOver() const
{
	return isBattleOver;
}
