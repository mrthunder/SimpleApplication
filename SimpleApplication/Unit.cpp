// Lucas de Souza Góes (c) 2020

// Includes
#include "Unit.h"
#include <algorithm>

// Using
using std::literals::string_literals::operator""s;
using std::clamp;
using std::to_string;


Unit::Unit(string unitName, int health, int attack, int defense, int speed, UT unitType)
	: name(unitName), maxHealth(health), attackPoints(attack), defensePoints(defense), speedPoints(speed), type(unitType)
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
	type = UnitType::Enemy;
}

void Unit::damage(int damage)
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

void Unit::defend()
{
	isDefending = true;
}

void Unit::resetTurn()
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

string Unit::getName() const
{
	return name;
}

UT Unit::getUnitType() const
{
	return type;
}

string Unit::getHealthUI() const
{
	return "Health: "s + to_string(currentHealth) + " / "s + to_string(maxHealth);
}

int Unit::getAttackDamage() const
{
	return attackPoints;
}

int Unit::getSpeed() const
{
	return speedPoints;
}

bool Unit::isUnitDead() const
{
	return isDead;
}
