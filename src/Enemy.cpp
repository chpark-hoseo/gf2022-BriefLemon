#include "Enemy.h"
#include <SDL2/SDL.h>

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	m_currentFrame = ((SDL_GetTicks() / 100) % 6);
}

void Enemy::clean() {}