#include "GameFramework/ArcadeScene.h"
#include "Graphics/Screen.h"
#include "Shapes/Rectangle2D.h"
#include "Shapes/Triangle.h"
#include "Shapes/Circle2D.h"
#include "Input/GameController.h"
#include "Framework/Core.h"

void ArcadeScene::Init()
{
	ButtonAction action;
	action.key = GameController::ActionKey();
	action.action = [](float dt, InputState state) {
		if (GameController::IsPressed(state))
		{
			snw::LOG("Action Button is pressed!");
		}
		};
	m_gameController.AddInputActionForKey(action);
}

void ArcadeScene::Tick(float dt)
{

}

void ArcadeScene::Render(Screen & screen)
{
	Rectangle2D rect(Vector2D(0.f, 0.f), 50, 60);
	Circle2D circ(Vector2D(screen.GetWidth() / 2.f, screen.GetHeight() / 2.f), 100.f);
	Triangle2D trig(Vector2D(200.f, 1.f), Vector2D(100.f, 100.f), Vector2D(300.f, 100.f));
	screen.ShapeRenderer().DrawShape(&rect, Color::Green(), true);
	screen.ShapeRenderer().DrawShape(circ, Color::Red());
	screen.ShapeRenderer().DrawShape(&trig, Color::Orange(), true, Color::Orange(), true);
}

const std::string& ArcadeScene::GetSceneName() const
{
	return "Arcade Scene";
}

std::unique_ptr<Scene> ArcadeScene::GetScene(arcadeGame game)
{
	switch (game)	
	{
	case arcadeGame::TETRIS:
		
		break;
	case arcadeGame::BREAK_OUT:
		break;
	case arcadeGame::ASTREOIDS:
		break;
	case arcadeGame::PACMAN:
		break;
	default:
		break;
	}
	return std::unique_ptr<Scene>();
}
