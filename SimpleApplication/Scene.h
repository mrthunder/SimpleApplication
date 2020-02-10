// Lucas de Souza Góes (C) 2020
#pragma once

// Includes
#include <string>
#include <chrono>

// Using(s)
using std::chrono::milliseconds;
using std::string;

// Forward Declarations
class Game;

class Scene
{
public: 
	virtual void update(Game* const gameRef, milliseconds time); // This method execute every frame
	virtual void draw(wchar_t* screen,const int screenHeight,const int screenWidth); // This method execute every frame
protected:
	/**
	 * Draws a character on the screen
	 * 
	 * \param screen The screen buffer
	 * \param screenWidth The width of the screen
	 * \param posX The x position on the screen where you want to draw the character
	 * \param posY The y position on the screen where you want to draw the character
	 * \param content The character to be drawn
	 */
	inline void drawToScreen(wchar_t* screen, const int screenWidth, int posX, int posY, wchar_t content) 
	{
		screen[posY * screenWidth + posX] = content;
	}

	/**
	 * Draws a string on the screen
	 *
	 * \param screen The screen buffer
	 * \param screenWidth The width of the screen
	 * \param posX The x start position on the screen where you want to start drawing your string
	 * \param posY The y start position on the screen where you want to start drawing your string
	 * \param content The string to be drawn
	 */
	inline void drawToScreen(wchar_t* screen, const int screenWidth, int posX, int posY, string content)
	{
		for (size_t i = 0; i < content.length(); i++)
		{
			screen[posY * screenWidth + (posX+i)] = content[i];
		}
		
	}
};

