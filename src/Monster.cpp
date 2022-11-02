#include "Monster.h"

void Monster::load(int x, int y, int width, int height, std::string textureID)
{
	GameObject::load(x, y, width, height, textureID);
}

void Monster::draw(SDL_Renderer* pRenderer)
{
	GameObject::draw(pRenderer);
}

void Monster::update(int spd)
{
	if (m_x > 640 - 128) { isRight = false; }
	else if (m_x < 0) { isRight = true; }

	if (isRight) { m_x += spd; }
	else { m_x -= spd; }
}