#pragma once
#include "Scene.h"
#include <vector>

using namespace std;

class Game;

class MainMenu :
	public Scene
{
public:
	virtual void Update(Game* const gameRef) override;
	virtual void Draw(wchar_t* screen, const int screenHeight, const int screenWidth) override;
private:
	vector<string> options{ "Play", "Exit" };
	int selectedOptionIndex = 0;
};

