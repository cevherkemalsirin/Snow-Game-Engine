#include "Game/GameScene.h"

GameScene::GameScene(snw::unique<Game> game):m_game(std::move(game))
{

}

void GameScene::Init()
{
	m_game->Init(m_gameController);
}

void GameScene::Tick(float deltaTime)
{
	m_game->Tick(deltaTime);
}

void GameScene::Render(Screen & screen)
{
	m_game->Render(screen);
}

const std::string& GameScene::GetSceneName() const
{
	static std::string name = "NoName";
	return name;

}