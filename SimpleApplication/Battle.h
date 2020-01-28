// Lucas de Souza Góes (C) 2020
#pragma once
#include <string>
#include <vector>
#include <memory>

class Unit;

class Battle
{
public:
	Battle(std::shared_ptr<Unit> player, Unit* enemy);
	void Update();
	void Draw(wchar_t* screen,const int screenWidth,const int screenHeight);
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
	std::vector<std::string> options{"Attack", "Defend", "Escape" };
	int selectedOptionIndex = 0;
	bool isBattleOver = false;
	std::shared_ptr<Unit> playerPtr;
	Unit* enemyPtr;

};

