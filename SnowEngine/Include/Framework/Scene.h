#pragma once
#include <string>
#include <Input/GameController.h>

class Screen;

class Scene {

public:
	virtual ~Scene() = default;

	virtual void Init() = 0;
	virtual void Tick(float deltaTime) = 0;
	virtual void Render(Screen& screen) = 0;
	virtual const std::string& GetSceneName() const = 0;

	GameController* GetGameController() { return &m_gameController; }
protected:
	GameController m_gameController;
};