#pragma once
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
	void Update();
	void Draw();
private:
	bool isGameRunning;
	wchar_t* screen;
	void* console;
	Scene* currentScene;
};

