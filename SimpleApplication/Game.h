// Lucas de Souza Góes (C) 2020
#pragma once
#include <chrono>
class Scene;


class Game
{
public:
	Game();
	~Game();
	void End();
	void ChangeScenes(Scene* newScene);
private:
	void GameLoop();
	void Update(std::chrono::milliseconds time, std::chrono::milliseconds deltaTime);
	void Draw();
private:
	bool isGameRunning;
	wchar_t* screen;
	void* console;
	Scene* currentScene;
	std::chrono::time_point<std::chrono::system_clock> initialTime;
	std::chrono::time_point<std::chrono::system_clock> currentTime;
	std::chrono::time_point<std::chrono::system_clock> startTimer;
	std::chrono::time_point<std::chrono::system_clock> endTimer;
};

