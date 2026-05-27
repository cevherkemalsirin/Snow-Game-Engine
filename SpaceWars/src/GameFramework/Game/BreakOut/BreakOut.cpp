#include "Game/BreakOut/BreakOut.h"
#include <string>
#include "Framework/Core.h"


void BreakOut::Init(GameController& controller)
{

	controller.ClearAll();
	ResetGame();
	ButtonAction leftKeyAction;
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](float dt, InputState state)
		{
			if (GameController::IsPressed(state))
			{
				m_paddle.SetMovementDirection(PaddleDirection::LEFT);
			}
			else
			{
				m_paddle.SetMovementDirection(PaddleDirection::STOP);
			}
		};
	
	controller.AddInputActionForKey(leftKeyAction);



	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](float dt, InputState state)
		{
			if (GameController::IsPressed(state))
			{
				m_paddle.SetMovementDirection(PaddleDirection::RIGHT);
			}
			else
			{
				m_paddle.SetMovementDirection(PaddleDirection::STOP);
			}
		};

	controller.AddInputActionForKey(rightKeyAction);
}

void BreakOut::Tick(float deltaTime)
{
	snw::LOG("Tick running for breakout");
	m_paddle.Tick(deltaTime);
}

void BreakOut::Render(Screen & screen)
{
	m_paddle.Render(screen);
	
}

std::string BreakOut::GetName() const
{
	return std::string();
}


void BreakOut::ResetGame() 
{
	Rectangle2D paddleRect = Rectangle2D{ Vector2D((600 / 2) - (Paddle::PADDLE_WIDTH / 2), (800 - 3 * Paddle::PADDLE_WIDTH)), Paddle::PADDLE_HEIGHT, Paddle::PADDLE_WIDTH };
	m_paddle.Init(paddleRect);
}