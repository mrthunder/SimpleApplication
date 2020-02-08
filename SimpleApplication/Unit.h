// Lucas de Souza Góes (C) 2020
#pragma once
#include <string>

class Unit
{
public:
	enum class UnitType {
		Player,
		Enemy
	};
public:
	Unit(std::string name, int health, int attack, int defense, int speed, UnitType unitType);
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
	UnitType type;
public:
	void Damage(int damage);
	void Defend();
	void ResetTurn();
	int getCurrentHealth() const;
	int getMaxHealth() const;
	std::string getName() const;
	UnitType getUnitType() const;
	std::string getHealthUI() const;
	int getAttackDamage() const;
	int getSpeed()const;
	bool IsDead() const;
};

