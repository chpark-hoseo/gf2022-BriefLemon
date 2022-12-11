#include "StartButton.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>
#include <iostream>

StartButton::StartButton(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void StartButton::draw()
{
	SDLGameObject::draw();
}

void StartButton::update()
{
	handleInput();
	SDLGameObject::update();
}

void StartButton::handleInput()
{
	if (TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
		Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
		std::cout << "Mouse Y : " << vec->getY() << ",";
		std::cout << "Button Y : " << m_position.getY() << "~"  << m_position.getY() + m_height << std::endl;

		if (vec->getX() >= m_position.getX() && vec->getX() < m_position.getX() + m_width && vec->getY() + SCREEN_HEIGHT * 2 >= m_position.getY() && vec->getY() + SCREEN_HEIGHT * 2 < m_position.getY() + m_height) {
			TheTextureManager::Instance()->destroyTexture("startScreen");
			TheTextureManager::Instance()->destroyTexture("startButton");
			TheTextureManager::Instance()->destroyTexture("exitButton");
		}
	}
}

void StartButton::clean() {}