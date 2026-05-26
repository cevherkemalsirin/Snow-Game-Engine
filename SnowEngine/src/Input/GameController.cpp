#include "Input/GameController.h"
#include <SDL3/SDL.h>

GameController::GameController()
{}

InputAction GameController::GetActionForKey(InputKey key)
{
	for (const auto& ButtonAction : m_buttonActions)
	{
		if (key == ButtonAction.key)
		{
			return ButtonAction.action;
		}
	 }
	return [](float, InputState) {};
}

void GameController::AddInputActionForKey(const ButtonAction& buttonAction)
{
	m_buttonActions.push_back(buttonAction);
}

void GameController::ClearAll()
{
	m_buttonActions.clear();
}

bool GameController::IsPressed(InputState state)
{
	return state == InputState::Pressed;
}

bool GameController::IsReleased(InputState state)
{
	return state == InputState::Released;
}

InputKey GameController::ActionKey()
{
	return  static_cast<InputKey>(SDLK_A);
}

InputKey GameController::CancelKey()
{
	return static_cast<InputKey>(SDLK_S);
}

InputKey GameController::LeftKey()
{
	return static_cast<InputKey>(SDLK_LEFT);
}

InputKey GameController::RightKey()
{
	return static_cast<InputKey>(SDLK_RIGHT);
}

InputKey GameController::UpKey()
{
	return static_cast<InputKey>(SDLK_UP);
}

InputKey GameController::DownKey()
{
	return static_cast<InputKey>(SDLK_DOWN);
}
