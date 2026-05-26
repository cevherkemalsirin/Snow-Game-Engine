#pragma once

#include <functional>

using InputKey = uint32_t;

enum class InputState : uint8_t
{
	Pressed,
	Released,
	Held
};

using InputAction = std::function<void(float dt, InputState)>;

struct ButtonAction
{
	InputKey key;
	InputAction action;
};