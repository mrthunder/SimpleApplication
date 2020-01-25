#pragma once
#include <string>

class Game;

class Scene
{
public: 
	virtual void Update(Game* const gameRef);
	virtual void Draw(wchar_t* screen,const int screenHeight,const int screenWidth);
protected:
	inline void DrawToScreen(wchar_t* screen, const int screenWidth, int posX, int posY, wchar_t content) 
	{
		screen[posY * screenWidth + posX] = content;
	}
	inline void DrawToScreen(wchar_t* screen, const int screenWidth, int posX, int posY, std::string content)
	{
		for (int i = 0; i < content.length(); i++)
		{
			screen[posY * screenWidth + (posX+i)] = content[i];
		}
		
	}
};

