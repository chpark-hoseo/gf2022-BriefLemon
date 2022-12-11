#pragma once
#include "SDLGameObject.h"

class StartButton : public SDLGameObject {
public:
	StartButton(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void handleInput();
};