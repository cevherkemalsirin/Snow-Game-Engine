#pragma once

#include "Game/Game.h"

class BreakOut : public Game
{
public:
	
	virtual void Init(GameController& controller) override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(Screen& screen) override;
	virtual std::string GetName() const override;

	virtual ~BreakOut() {};

private:

};
