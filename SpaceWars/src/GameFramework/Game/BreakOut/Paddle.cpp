#include "Game/Breakout/Paddle.h"
#include "Graphics/Screen.h"
void Paddle::Init(const Rectangle2D& rect)
{
	Excluder::Init(rect);
	m_direction = PaddleDirection::STOP;
}

void Paddle::Tick(float deltaTime)
{
	if (m_direction != PaddleDirection::STOP)
	{
		Vector2D dir;
		if (IsMovingLeft())
		{
			dir = LEFT_DIR;
		}
		else
		{
			dir = RIGTH_DIR;
		}
		Vector2D dx = dir * VELOCITY * deltaTime;

		MoveBy(dx);
	}
}

void Paddle::Render(Screen & screen)
{
	screen.ShapeRenderer().DrawShape(&GetRectangle(), Color::Blue(), true, Color::Blue());
	
}
