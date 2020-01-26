// Lucas de Souza Góes (C) 2020
#pragma once
#include "Scene.h"
#include <memory>

class Battle;

class Colliseum :
	public Scene
{
public:
	Colliseum();
	virtual void Update(Game* const gameRef) override;
	virtual void Draw(wchar_t* screen, const int screenHeight, const int screenWidth) override;
private:
	std::shared_ptr<Battle> battlePtr;
};

