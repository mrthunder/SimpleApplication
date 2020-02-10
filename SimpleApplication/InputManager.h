// Lucas de Souza Góes (c) 2020
#pragma once

// Includes
#include <Windows.h>
#include <map>

// Using
using std::map;

enum class KeyCode : int
{
	ArrowUp = VK_UP,
	ArrowDown = VK_DOWN,
	ArrowLeft = VK_LEFT,
	ArrowRight = VK_RIGHT,
	Z = 0x5A,
	X = 0x58,
	Return = VK_RETURN
};

class InputManager
{
public:
	// Returns true if the key provided was pressed this frame
	static bool getKeyDown(KeyCode key)
	{
		if (getKey(key) && keyState[key]) {
			return false;
		}
		else if (getKey(key) && !keyState[key])
		{
			updateOneKey(key);
			return true;
		}
		else {
			updateOneKey(key);
			return false;
		}

	}


private:

	// Update the key on the map
	static void updateOneKey(KeyCode key)
	{
		if (getKey(key) && !keyState[key])
		{
			keyState[key] = true;
		}
		else if (!getKey(key) && keyState[key])
		{
			keyState[key] = false;
		}
	}

	// Get the state of the key, if pressed true otherwise false
	static bool getKey(KeyCode key)
	{
		// The value 0x8000 contains the bit flag that tests whether the key is currently pressed.
		const DWORD FLAG = 0x8000;
		return GetKeyState(static_cast<int>(key))& FLAG;
	}

	//False is up and true is down
	static map<KeyCode, bool> keyState;
};

