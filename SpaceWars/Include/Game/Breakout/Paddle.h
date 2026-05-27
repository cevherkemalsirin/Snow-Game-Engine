#pragma once

#include "Excluder.h"


class Screen;

enum class PaddleDirection
{
	STOP = 0,
	LEFT,
	RIGHT
};

class Paddle : public Excluder
{
public:
	static const int PADDLE_WIDTH = 100;
	static const int PADDLE_HEIGHT = 30;

	void Init(const Rectangle2D& rect);

	void Tick(float deltaTime);

	void Render(Screen& screen);


	inline bool IsMovingLeft() const { return m_direction == PaddleDirection::LEFT; }
	inline bool IsMovingRight() const { return m_direction == PaddleDirection::RIGHT; }
	inline void StopMovement() { m_direction = PaddleDirection::STOP; }
	void SetMovementDirection(PaddleDirection dir);
private:
	PaddleDirection m_direction;

	const float VELOCITY = 50.f;
};