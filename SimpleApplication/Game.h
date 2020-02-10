// Lucas de Souza Góes (C) 2020
#pragma once

//Include
#include <chrono>

// Using(s)
using std::chrono::milliseconds;
using std::chrono::time_point;
using std::chrono::system_clock;

// Forward Declaration
class Scene;

class Game
{
public:
	Game(); //Ctor
	~Game(); //Dtor
	void end(); // Ends the game
	void changeScenes(Scene* newScene); // Change from the current scene to the next
private:
	void gameLoop(); // Contains the game loop
	void update(milliseconds time); // This method will execute every frame
	void draw(); // This method will execute every frame
private:
	bool isGameRunning; // This property keeps the game looping
	wchar_t* screen; // This is the screen buffer, 
	                 // and what ever gets add to the buffer shows on the screen
	void* console; // Console Handle
	Scene* currentScene; // Current Scene being displayed
	time_point<system_clock> initialTime;  // When the game started
	time_point<system_clock> currentTime; // The current time
	time_point<system_clock> startTimer; // Start of the frame
	time_point<system_clock> endTimer; // End of the frame
	milliseconds timer; // In game timer
	milliseconds deltaTime; // How long did the frame took to finish
};

