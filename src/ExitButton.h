#pragma once
#include "SDLGameObject.h"

class ExitButton : public SDLGameObject {
public:
	ExitButton(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void handleInput();
};