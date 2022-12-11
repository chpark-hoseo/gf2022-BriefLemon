#include "ScreenManager.h"
#include "TextureManager.h"
#include "StartButton.h"
#include "ExitButton.h"

void ScreenManager::init(Player* player, SDL_Renderer* renderer) {
    this->m_player = player;
    this->m_pRenderer = renderer;

	StartButton* startButton = new StartButton(new LoaderParams(140, 1900, 360, 120, "startButton", 0, 0, SDL_FLIP_NONE));
	ExitButton* exitButton = new ExitButton(new LoaderParams(140, 2100, 360, 120, "exitButton", 0, 0, SDL_FLIP_NONE));

    m_buttons.push_back(startButton);
    m_buttons.push_back(exitButton);
}

void ScreenManager::draw() {
    
    TheTextureManager::Instance()->drawFrame("startScreen", 0, SCREEN_HEIGHT * 2, 640, 768, 0, 0, m_pRenderer);
    for (auto& buttons : m_buttons)
    {
        buttons->draw();
    }

    if (isClear)
        TheTextureManager::Instance()->drawFrame("clearScreen", 0, 0, 640, 768, 0, 0, m_pRenderer);
}

void ScreenManager::update() {
    for (auto& buttons : m_buttons)
    {
        buttons->update();
    }

    if (m_player->getYpos() < 0) isClear = true;
}

void ScreenManager::clean() {
    for (auto& buttons : m_buttons)
    {
        buttons->clean();
    }
}

ScreenManager* ScreenManager::s_pInstance = 0;