// Lucas de Souza Góes (C) 2020
#pragma once

//Includes
#include <string>

// Using(s)
using std::string;

class Unit
{
public:
	// The type of the unit
	enum class UnitType {
		Player, // Can be controlled by the user
		Enemy // Cannot be controlled by the user
	};
public:
	// This constructor will generate an specific unit based on the parameters
	Unit(string name, int health, int attack, int defense, int speed, UnitType unitType);
	Unit(); // This constructor will generate a random unit
private:
	string name; // The name of the unit
	int maxHealth; // The total health the unit have
	int currentHealth; // How much health does the unit current have
	int attackPoints; // How strong is the unit
	int defensePoints; // How much can the unit defend
	int speedPoints; // How fast is the unit
	bool isDefending; // Returns the battle state of the unit
	bool isDead; // Returns that state of the unit
	UnitType type; // The type of the unit
public:
	void damage(int damageAmount); // Deals damage to this unit
	void defend(); // Set the unit in the defense position
	void resetTurn(); // Reset all the properties that were set on the previous turn
	int getCurrentHealth() const; // Get the current health
	int getMaxHealth() const; // Get the max health
	string getName() const; // Get the name of the unit
	UnitType getUnitType() const; // Get the unit type
	string getHealthUI() const; // Returns a string with - current health / max health
	int getAttackDamage() const; // Get the attack property
	int getSpeed() const; // Get the speed property
	bool isUnitDead() const; // Check if the unit is dead
};

