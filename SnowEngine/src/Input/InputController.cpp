#include "Input/InputController.h"
#include <iostream>
#include "Input/GameController.h"
#include <SDL3/SDL.h>

InputController::InputController(InputAction quitAction):m_currentController(nullptr), m_quitAction(quitAction)
{

}

void InputController::Tick(float deltaTime)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_EVENT_KEY_DOWN:
				//snw::LOG("Key Down: {}", event.key.key);
			case SDL_EVENT_KEY_UP:
				if (m_currentController)
				{
					InputAction action = m_currentController->GetActionForKey(event.key.key);
					std::cout << event.key.key << std::endl;
					InputState state = event.key.down ? InputState::Pressed : InputState::Released;

					action(deltaTime, state);
				}
				break;
			case SDL_EVENT_QUIT:
				m_quitAction(deltaTime, InputState::Pressed);
				break;
			default:
				break;
		}
	}

}

void InputController::SetGameController(GameController * controller)
{
	m_currentController = controller;
}
