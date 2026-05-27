#include "Game/BreakOut/BreakOut.h"
#include <string>
#include "Framework/Core.h"

void BreakOut::Init(GameController& controller)
{

}

void BreakOut::Tick(float deltaTime)
{
	snw::LOG("Tick running for breakout");
}

void BreakOut::Render(Screen & screen)
{}

std::string BreakOut::GetName() const
{
	return std::string();
}
