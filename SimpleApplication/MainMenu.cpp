// Lucas de Souza Góes (C) 2020
#include "MainMenu.h"
#include "InputManager.h"
#include "Game.h"
#include "Colliseum.h"

void MainMenu::Update(Game* const gameRef)
{
	if (InputManager::GetKeyDown(KeyCode::ArrowDown))
	{
		selectedOptionIndex++;
		if (selectedOptionIndex >= 2) 
		{
			selectedOptionIndex = 1;
		}
	}
	else if (InputManager::GetKeyDown(KeyCode::ArrowUp))
	{
		selectedOptionIndex--;
		if (selectedOptionIndex <0) 
		{
			selectedOptionIndex = 0;
		}
	}
	else if (InputManager::GetKeyDown(KeyCode::Z) || InputManager::GetKeyDown(KeyCode::Return))
	{
		if (selectedOptionIndex == 1)
		{
			gameRef->End();
		}
		else 
		{
			gameRef->ChangeScenes(new Colliseum());
		}
	}
	

}

void MainMenu::Draw(wchar_t* screen, const int screenHeight, const int screenWidth)
{
	DrawToScreen(screen, screenWidth, 52, 20, "Simple Application");
	for (size_t i = 0; i < options.size();i++)
	{
		string option = options[i];
		if (selectedOptionIndex == i)
		{
			option = "> " + options[i];
			DrawToScreen(screen, screenWidth, 58, 25 + (5 * i), option);
		}
		else
		{
			DrawToScreen(screen, screenWidth, 60, 25 + (5 * i), option);
		}
		
		
	}
	
}
