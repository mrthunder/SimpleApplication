// Lucas de Souza Góes (C) 2020
#pragma once

// Includes
#include "Scene.h"
#include <memory>
#include <vector>

// Using(s)
using std::chrono::milliseconds;
using std::shared_ptr;
using std::vector;

// Forward Declarations
class Unit;
class Battle;

class Colliseum :
	public Scene
{
public:
	Colliseum();
	~Colliseum();
	virtual void update(Game* const gameRef, milliseconds time) override;
	virtual void draw(wchar_t* screen, const int screenHeight, const int screenWidth) override;
private:
	shared_ptr<Battle> battlePtr;
	vector<shared_ptr<Unit>> playerParty{};

};

