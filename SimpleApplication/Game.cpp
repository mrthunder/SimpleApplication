// Lucas de Souza Góes (C) 2020

// Includes
#include "Game.h"
#include <thread>
#include <Windows.h>
#include "MainMenu.h"

// Using(s)
using std::chrono::duration_cast;
using std::literals::chrono_literals::operator""ms;
using std::this_thread::sleep_for;

// Constants
const int SCREEN_HEIGHT = 40;
const int SCREEN_WIDTH = 120;


Game::Game()
{
	// Initializing the console buffer for the draw function to work
	screen = new wchar_t[SCREEN_HEIGHT * SCREEN_WIDTH];
	console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(console);
	SetConsoleScreenBufferSize(console, { SCREEN_WIDTH,SCREEN_HEIGHT });

	//Remove the cursor from the screen
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(console, &cursorInfo);

	// Initializing the game
	initialTime = system_clock::now();
	changeScenes(new MainMenu());
	this->isGameRunning = true;
	this->gameLoop();
}

Game::~Game()
{
	delete currentScene;
}

void Game::gameLoop()
{
	while (isGameRunning)
	{
		currentTime = system_clock::now();
		timer = duration_cast<milliseconds>(endTimer - initialTime);
		deltaTime = duration_cast<milliseconds>(endTimer - startTimer);
		startTimer = system_clock::now();
		update(timer);
		draw();
		endTimer = system_clock::now();
		if (50ms - deltaTime > 0ms)
		{
			sleep_for(50ms - deltaTime);
		}
	}
}


void Game::update(milliseconds time)
{
	currentScene->update(this, time);
}

void Game::draw()
{
	constexpr COORD startCoordinates = { 0,0 };
	DWORD bytesWritten = 0;
	constexpr int screenLength = SCREEN_HEIGHT * SCREEN_WIDTH;
	// Clearing the screen
	for (int i = 0; i < screenLength; i++)
	{
		screen[i] = ' ';
	}
	// Repositioning the cursor at the top left
	SetConsoleCursorPosition(console, { 0,0 });
	currentScene->draw(screen, SCREEN_HEIGHT, SCREEN_WIDTH);
	WriteConsoleOutputCharacter(console, screen, SCREEN_WIDTH * SCREEN_HEIGHT, startCoordinates, &bytesWritten);
	
}

void Game::end()
{
	isGameRunning = false;
	CloseHandle(console);
}

void Game::changeScenes(Scene* newScene)
{
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
	}
	currentScene = newScene;
}
