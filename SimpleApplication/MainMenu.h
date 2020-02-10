// Lucas de Souza Góes (C) 2020
#pragma once

// Includes
#include "Scene.h"
#include <vector>

// Using(s)
using std::vector;

// Forward Declarations
class Game;

class MainMenu :
	public Scene
{
public:
	virtual void update(Game* const gameRef, milliseconds time) override;
	virtual void draw(wchar_t* screen, const int screenHeight, const int screenWidth) override;
private:
	vector<string> options{ "Play", "Exit" }; // Menu options
	int selectedOptionIndex = 0; // The index of the option that is currently selected on the main menu

};

