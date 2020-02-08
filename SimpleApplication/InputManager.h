#pragma once
#include <Windows.h>
#include <map>

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
	static bool GetKeyDown(KeyCode key)
	{
		if (GetKey(key) && keyState[key]) {
			return false;
		}
		else if (GetKey(key) && !keyState[key])
		{
			UpdateOneKey(key);
			return true;
		}
		else {
			UpdateOneKey(key);
			return false;
		}

	}


private:

	static void UpdateOneKey(KeyCode key)
	{
		if (GetKey(key) && !keyState[key])
		{
			keyState[key] = true;
		}
		else if (!GetKey(key) && keyState[key])
		{
			keyState[key] = false;
		}
	}

	static bool GetKey(KeyCode key)
	{
		// The value 0x8000 contains the bit flag that tests whether the key is currently pressed.
		const DWORD FLAG = 0x8000;
		return GetKeyState(static_cast<int>(key))& FLAG;
	}
	//False is up and true is down
	static map<KeyCode, bool> keyState;
};

