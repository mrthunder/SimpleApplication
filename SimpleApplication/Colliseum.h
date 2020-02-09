// Lucas de Souza Góes (C) 2020
#pragma once
#include "Scene.h"
#include <memory>
#include <vector>

class Unit;
class Battle;

class Colliseum :
	public Scene
{
public:
	Colliseum();
	~Colliseum();
	virtual void Update(Game* const gameRef, std::chrono::milliseconds time, std::chrono::milliseconds deltaTime) override;
	virtual void Draw(wchar_t* screen, const int screenHeight, const int screenWidth) override;
private:
	std::shared_ptr<Battle> battlePtr;
	std::vector<std::shared_ptr<Unit>> playerParty{};

};

