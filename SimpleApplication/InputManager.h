#pragma once
#include <Windows.h>

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
		// The value 0x8000 contains the bit flag that tests whether the key is currently pressed.
		const DWORD FLAG = 0x8000;
		return GetKeyState(static_cast<int>(key)) & FLAG;
	}

	static bool GetKeyUp(KeyCode key)
	{
		return !GetKeyDown(key);
	}
};

