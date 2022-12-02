#pragma once
#include "LoaderParams.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 768;

class GameObject {

public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual ~GameObject() {}

protected:
	GameObject(const LoaderParams* pParams) {}
};