#include "ExitButton.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"
#include <SDL2/SDL.h>

ExitButton::ExitButton(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void ExitButton::draw()
{
	SDLGameObject::draw();
}

void ExitButton::update()
{
	handleInput();
	SDLGameObject::update();
}

void ExitButton::handleInput()
{
	if (TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
		Vector2D* vec = TheInputHandler::Instance()->getMousePosition();

		if (vec->getX() >= m_position.getX() && vec->getX() < m_position.getX() + m_width && vec->getY() + SCREEN_HEIGHT * 2 >= m_position.getY() && vec->getY() + SCREEN_HEIGHT * 2 < m_position.getY() + m_height) {
			TheGame::Instance()->quit();
		}
	}
}

void ExitButton::clean() {}