// Lucas de Souza Góes (C) 2020
 
//Includes
#include "MainMenu.h"
#include "InputManager.h"
#include "Game.h"
#include "Colliseum.h"

// Using
using std::literals::string_literals::operator""s;

void MainMenu::update(Game* const gameRef, milliseconds time)
{
	// Selecting the option
	if (InputManager::getKeyDown(KeyCode::ArrowDown))
	{
		selectedOptionIndex++;
		if (selectedOptionIndex >= 2) 
		{
			selectedOptionIndex = 1;
		}
	}
	else if (InputManager::getKeyDown(KeyCode::ArrowUp))
	{
		selectedOptionIndex--;
		if (selectedOptionIndex <0) 
		{
			selectedOptionIndex = 0;
		}
	}
	else if (InputManager::getKeyDown(KeyCode::Z) || InputManager::getKeyDown(KeyCode::Return))
	{
		if (selectedOptionIndex == 1)
		{
			gameRef->end();
		}
		else 
		{
			gameRef->changeScenes(new Colliseum());
		}
	}
	

}

void MainMenu::draw(wchar_t* screen, const int screenHeight, const int screenWidth)
{
	// Title
	drawToScreen(screen, screenWidth, 52, 20, "Simple Application"s);
	// Drawing the menu options
	for (size_t i = 0; i < options.size();i++)
	{
		string option = options[i];
		if (selectedOptionIndex == i)
		{
			option = "> " + options[i];
			drawToScreen(screen, screenWidth, 58, 25 + (5 * i), option);
		}
		else
		{
			drawToScreen(screen, screenWidth, 60, 25 + (5 * i), option);
		}
		
		
	}
	
}
