#pragma once

#include <functional>

using InputKey = uint32_t;
using MouseButton = uint8_t;

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

struct MousePosition
{
	int32_t xPos;
	int32_t yPos;
};

using MouseMovedAction = std::function<void(const MousePosition& mousePoisiton)>;
using MouseInputAction = std::function<void(InputState state, const MousePosition& mousePosition)>;

struct MouseButtonAction
{
	MouseButton mouseButton;
	MouseInputAction mouseInputAction;
};