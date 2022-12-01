#pragma once

#include "SDLGameObject.h"
#include <SDL2/SDL.h>

class Tile : public SDLGameObject
{
public:
	Tile(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void handleInput() {};
	void init(int ranX, int ranY);

	int getXpos();
	int getYpos();
	int getWidth();
	int getHeight();

private:
};