#include "Player.h"
#include <SDL2/SDL.h>

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_currentFrame = ((SDL_GetTicks() / 100) % 6);
	m_position.setX(2);
}

void Player::clean() {}