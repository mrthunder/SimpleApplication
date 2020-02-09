// Lucas de Souza Góes (C) 2020
#pragma once
#include "Scene.h"
#include <vector>


class Game;

class MainMenu :
	public Scene
{
public:
	virtual void Update(Game* const gameRef, std::chrono::milliseconds time, std::chrono::milliseconds deltaTime) override;
	virtual void Draw(wchar_t* screen, const int screenHeight, const int screenWidth) override;
private:
	std::vector<std::string> options{ "Play", "Exit" };
	int selectedOptionIndex = 0;

};

