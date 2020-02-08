#include "InputManager.h"

map<KeyCode, bool> InputManager::keyState {
	{KeyCode::ArrowDown, false},
	{ KeyCode::ArrowUp , false },
	{ KeyCode::ArrowLeft , false },
	{ KeyCode::ArrowRight , false },
	{ KeyCode::Z , false },
	{ KeyCode::X , false },
	{ KeyCode::Return , false }
};