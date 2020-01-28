#include "InputSystem.h"

bool KeyboardState::getKeyValue(SDL_Scancode scanCode) {
	return mCurrState[scanCode] == 1;
}

ButtonState KeyboardState::getKeyState(SDL_Scancode scanCode) {
	if (mPrevState[scanCode] == 0) {
		if (mCurrState[scanCode] == 0) {
			return ENone;
		}
		else return EPressed;
	}
	else {
		if (mCurrState[scanCode] == 0) {
			return EReleased;
		}
		else return EHeld;
	}
}

bool MouseState::getButtonValue(int button) {
	return (mPrevButton && SDL_BUTTON(button));
}

ButtonState MouseState::getButtonState(int button) {
	button = SDL_BUTTON(button);
	
	if((mPrevButton & button) == 0) {
		if ((mCurrButton & button) == 0) {
			return ENone;
		}
		else return EPressed;
	}
	else {
		if ((mCurrButton & button) == 1) {
			return EReleased;
		}
		else return EHeld;
	}
}

bool InputSystem::Initialize() {
	//keyboard
	mInputState.keyboard.mCurrState = SDL_GetKeyboardState(NULL);
	memset(mInputState.keyboard.mPrevState, 0, SDL_NUM_SCANCODES);

	// mouse
	mInputState.mouse.mCurrButton = mInputState.mouse.mPrevButton = 0;
	mInputState.mouse.IsRelative = false;
	mInputState.mouse.mScrollWheel = Vector2::Zero;

	return true;
}

void InputSystem::PrepreForUpdate() {
	memcpy(mInputState.keyboard.mPrevState, mInputState.keyboard.mCurrState, SDL_NUM_SCANCODES);

	mInputState.mouse.mPrevButton = mInputState.mouse.mCurrButton;

}

void InputSystem::Update() {
	mInputState.keyboard.mCurrState = SDL_GetKeyboardState(NULL);

	int x =0, y =0;

	if (mInputState.mouse.IsRelative) {
		mInputState.mouse.mCurrButton = SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		mInputState.mouse.mCurrButton = SDL_GetMouseState(&x, &y);
	}

	mInputState.mouse.mMousePos.x = static_cast<float>(x);
	mInputState.mouse.mMousePos.y = static_cast<float>(y);


}

void InputSystem::ProcessEvent(SDL_Event& event) {
	switch (event.type) {
	case SDL_MOUSEWHEEL: 
		mInputState.mouse.mScrollWheel = Vector2(
			static_cast<float>(event.wheel.x),
			static_cast<float>(event.wheel.y));
		break;
	}
}

void InputSystem::setRelativeMode(bool value) {
	SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);
	mInputState.mouse.IsRelative = value;
}