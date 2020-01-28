#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_scancode.h>
#include <SDL/SDL_mouse.h>
#include "Math.h"

using namespace std;

enum ButtonState {
	ENone,
	EPressed,
	EReleased,
	EHeld
};

class KeyboardState {
public:
	friend class InputSystem;

	bool getKeyValue(SDL_Scancode scanCode);

	ButtonState getKeyState(SDL_Scancode scanCode);
private:
	const Uint8* mCurrState;
	Uint8 mPrevState[SDL_NUM_SCANCODES];

};

class MouseState {
public:
	friend class InputSystem;

	const Vector2& getPosition() { return mMousePos; }

	const Vector2& getScrollWheel() { return mScrollWheel; }

	bool isRelative() { return IsRelative; }

	bool getButtonValue(int button);

	// 1 left button
	// 2 middle button
	// 3 right button
	ButtonState getButtonState(int button);
private:
	Vector2 mMousePos;
	Vector2 mScrollWheel;

	Uint32 mCurrButton;
	Uint32 mPrevButton;

	bool IsRelative;
};

struct InputState {
	KeyboardState keyboard;

	MouseState mouse;
};

class InputSystem {
public:
	bool Initialize();

	void PrepreForUpdate();

	void Update();

	void ProcessEvent(SDL_Event& event);

	InputState getInputState() { return mInputState; }

	void setRelativeMode(bool value);

private:
	InputState mInputState;
};