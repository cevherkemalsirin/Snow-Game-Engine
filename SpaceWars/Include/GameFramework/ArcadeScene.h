#pragma once


#include <Framework/Scene.h>
#include <memory>


enum class arcadeGame {
	TETRIS = 0,
	BREAK_OUT,
	ASTREOIDS,
	PACMAN,
	NUM_GAMES
};

class ArcadeScene : public Scene
{
public:
	ArcadeScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(Screen& screen) override;
	virtual const std::string& GetSceneName() const override;

private:
	std::unique_ptr<Scene> GetScene(arcadeGame game);
};
