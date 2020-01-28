// Lucas de Souza Góes (C) 2020
#pragma once
#include <string>

class Unit
{
public:
	Unit(std::string name, int health, int attack, int defense, int speed);
	Unit();
private:
	std::string name;
	int maxHealth;
	int currentHealth;
	int attackPoints;
	int defensePoints;
	int speedPoints;
	bool isDefending;
	bool isDead;
public:
	void Damage(int damage);
	void Defend();
	void ResetTurn();
	int getCurrentHealth() const;
	int getMaxHealth() const;
	std::string getName() const;
	std::string getHealthUI() const;
};

