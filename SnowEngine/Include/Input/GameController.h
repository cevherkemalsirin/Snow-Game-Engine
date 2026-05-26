#pragma once

#include "InputAction.h"
#include <vector>

class GameController
{
public:
	GameController();
	InputAction GetActionForKey(InputKey key);
	
	void AddInputActionForKey(const ButtonAction& buttonAction);
	void ClearAll();

	static bool IsPressed(InputState state);
	static bool IsReleased(InputState state);
	static InputKey ActionKey();
	static InputKey CancelKey();
	static InputKey LeftKey();
	static InputKey RightKey();
	static InputKey UpKey();
	static InputKey DownKey();

	inline const MouseMovedAction& GetMouseMovedAction() { return m_mouseMovedAction; }

	inline void SetMouseMovedAction(const MouseMovedAction& action) { m_mouseMovedAction = action; }

	MouseInputAction GetMouseButtonAction(MouseButton button);

	void AddMouseButtonAction(const MouseButtonAction& mouseButtonAction);

	static MouseButton LeftMouseButton();
	static MouseButton RightMouseButton();


 private:
	std::vector<ButtonAction> m_buttonActions;
	std::vector<MouseButtonAction> m_moouseButtonActions;
	MouseMovedAction m_mouseMovedAction;
};