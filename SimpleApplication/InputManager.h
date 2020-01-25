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
	Return = VK_RETURN,
	GamepadLeftThumpstickUp = VK_GAMEPAD_LEFT_THUMBSTICK_UP,
	GamepadLeftThumpstickDown = VK_GAMEPAD_LEFT_THUMBSTICK_DOWN,
	GamepadLeftThumpstickLeft = VK_GAMEPAD_LEFT_THUMBSTICK_LEFT,
	GamepadLeftThumpstickRight = VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT,
	GamepadButtonA = VK_GAMEPAD_A,
	GamepadButtonB = VK_GAMEPAD_B,
	GamepadButtonMenu = VK_GAMEPAD_MENU,
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

