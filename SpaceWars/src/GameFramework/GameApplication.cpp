#include "GameFramework/GameApplication.h"
#include "Framework/World.h"
#include "Framework/Actor.h"
#include "Shapes/Rectangle2D.h"
#include "Shapes/Triangle.h"
#include "Shapes/Circle2D.h"
#include  "AI/AStar/Grid.h"
#include "AI/AStar/AStarSolver.h"

float x;
snw::Application* GetApplication()
{
	return new snw::GameApplication{};
	x = 0;
}

namespace snw
{


	GameApplication::GameApplication()
	{
		 weak<World> world = LoadWorld<World>();
		 actor = world.lock()->SpawnActor<Actor>();
	}

	void GameApplication::Tick(float dt)
	{
		x += dt;
		if (x > 2.f)
		{
			if (!actor.expired())
			{
				actor.lock()->Destroy();
			}
				
		}
	}

	void GameApplication::Render()
	{
		
		Rectangle2D rect(Vector2D(0.f, 0.f), 50, 60);
		Circle2D circ(Vector2D(m_width / 2.f, m_height / 2.f), 100.f);
		Triangle2D trig(Vector2D(200.f, 1.f), Vector2D(100.f, 100.f), Vector2D(300.f, 100.f));
	//	m_screen.ShapeRenderer().DrawShape(&rect, Color::Green(), true);
	//	m_screen.ShapeRenderer().DrawShape(circ, Color::Red());
	//	m_screen.ShapeRenderer().DrawShape(&trig, Color::Orange(), true, Color::Orange(), true);
		
		Grid grid(10, 10, 60, 60);
		grid.SetStartNode(0, 0);
		grid.setEndNode(3, 3);
		grid.setWallNode(5, 5);
		grid.setWallNode(3, 2);
		AStarSolver solver;
		//solver.Solve(grid);
		m_screen.ShapeRenderer().DrawGrid(grid);
	
	}

}

