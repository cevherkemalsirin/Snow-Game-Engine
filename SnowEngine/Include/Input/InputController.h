#pragma once
#include "InputAction.h"


class GameController;

class InputController
{
public:
	//takes function for quitting
	InputController(InputAction quitAction);

	void Tick(float deltaTime);
	void SetGameController(GameController* controller);
private:
	InputAction m_quitAction;
	//not owner
	GameController* m_currentController;
};
