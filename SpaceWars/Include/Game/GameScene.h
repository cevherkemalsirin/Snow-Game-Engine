#pragma once

#include "Game/Game.h"
#include "FrameWork/Scene.h"
#include "FrameWork/Core.h"

class GameScene :public Scene {

public:
	GameScene(snw::unique<Game> game);
	virtual ~GameScene() {}

	virtual void Init() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render(Screen& screen) override;

	virtual const std::string& GetSceneName() const override;
private:
	snw::unique<Game> m_game;

};