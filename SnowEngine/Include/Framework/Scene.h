#pragma once
#include <string>


class Screen;

class Scene {

public:
	virtual ~Scene() = default;

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(Screen& screen) = 0;
	virtual const std::string& GetSceneName() const = 0;

};