#pragma once

#include <string>

class GameController;
class Screen;

class Game
{
public:
	virtual ~Game() {};
	virtual void Init(GameController& controller) = 0;
	virtual void Tick(float deltaTime) = 0;
	virtual void Render(Screen& screen);
	virtual std::string GetName() const = 0;
};