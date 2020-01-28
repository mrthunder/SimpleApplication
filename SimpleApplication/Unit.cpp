#include "Unit.h"
#include <algorithm>

using namespace std;

Unit::Unit(string unitName, int health, int attack, int defense, int speed)
	: name(unitName), maxHealth(health), attackPoints(attack), defensePoints(defense), speedPoints(speed)
{
	currentHealth = maxHealth;
	isDead = false;
	isDefending = false;
}

Unit::Unit()
{
	//Random Ctor
	name = "Random Unit"s;
	maxHealth = rand() % 100;
	currentHealth = maxHealth;
	attackPoints = rand() % 10;
	defensePoints = rand() % 10;
	speedPoints = rand() % 5;
	isDead = false;
	isDefending = false;
}

void Unit::Damage(int damage)
{
	int currentDamage = damage - (defensePoints/2);
	if (isDefending)
	{
		currentDamage = damage - defensePoints;
	}
	currentDamage = clamp(currentDamage, 0, currentHealth);
	currentHealth -= currentDamage;
	if (currentHealth == 0)
	{
		isDead = true;
	}
}

void Unit::Defend()
{
	isDefending = true;
}

void Unit::ResetTurn()
{
	isDefending = false;
}

int Unit::getCurrentHealth() const
{
	return currentHealth;
}

int Unit::getMaxHealth() const
{
	return maxHealth;
}

std::string Unit::getName() const
{
	return name;
}

std::string Unit::getHealthUI() const
{
	return "Health: "s + to_string(currentHealth) + " / "s + to_string(maxHealth);
}
