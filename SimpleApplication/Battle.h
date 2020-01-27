// Lucas de Souza Góes (C) 2020
#pragma once
#include <string>
#include <vector>

using namespace std;

class Battle
{
public:
	
	void Update();
	void Draw(wchar_t* screen, int screenWidth, int screenHeight);
	bool IsBattleOver() const;
private:
	inline void DrawToScreen(wchar_t* screen, const int screenWidth, int posX, int posY, std::string content)
	{
		for (size_t i = 0; i < content.length(); i++)
		{
			screen[posY * screenWidth + (posX + i)] = content[i];
		}

	}
private:
	vector<string> options{"Attack"s, "Defend"s, "Escape"s };
	int selectedOptionIndex = 0;
	bool isBattleOver = false;

};

