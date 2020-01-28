// Lucas de Souza Góes (C) 2020
#include "Game.h"
#include <thread>
#include <chrono>
#include <Windows.h>
#include "MainMenu.h"

using namespace std;


const int SCREEN_HEIGHT = 40;
const int SCREEN_WIDTH = 120;


Game::Game()
{
	// Initializing the console buffer for the draw function to work
	screen = new wchar_t[SCREEN_HEIGHT * SCREEN_WIDTH];
	console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(console);
	// Initializing the game
	ChangeScenes(new MainMenu());
	this->isGameRunning = true;
	this->GameLoop();
}

Game::~Game()
{
	delete currentScene;
}

void Game::GameLoop()
{
	while (isGameRunning)
	{
		Update();
		Draw();
		std::this_thread::sleep_for(100ms);
	}
	
}


void Game::Update()
{
	currentScene->Update(this);
}

void Game::Draw()
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
	WriteConsoleOutputCharacter(console, screen, SCREEN_WIDTH * SCREEN_HEIGHT, startCoordinates, &bytesWritten);
	currentScene->Draw(screen, SCREEN_HEIGHT, SCREEN_WIDTH);
	screen[screenLength - 1] = '\0';
	WriteConsoleOutputCharacter(console, screen, SCREEN_WIDTH * SCREEN_HEIGHT, startCoordinates, &bytesWritten);
	
}

void Game::End()
{
	isGameRunning = false;
	CloseHandle(console);
}

void Game::ChangeScenes(Scene* newScene)
{
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
	}
	currentScene = newScene;
}
