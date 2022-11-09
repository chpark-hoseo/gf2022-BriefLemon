#include "Game.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        //윈도우 생성
        m_pWindow = SDL_CreateWindow(
            title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if (m_pRenderer != 0) {
                SDL_SetRenderDrawColor(
                    m_pRenderer, 0, 0, 0, 255);
            }
            else {
                return false; // 랜더러 생성 실패
            }
        }
        else {
            return false; // 윈도우 생성 실패
        }

        GameObject* m_go = new GameObject();
        GameObject* m_player = new Player();

        //Texture 생성
        if (!TheTextureManager::Instance()->load("assets/player.png", "Player", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/starBG.png", "BG", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/Floor.png", "Floor", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/platform.png", "Platform", m_pRenderer)) { return false; }

        m_go->load(100, 100, 128, 82, "Player");
        m_player->load(300, 300, 128, 82, "Player");
        m_gameObjects.push_back(m_go);
        m_gameObjects.push_back(m_player);
    }
    else {
        return false; // SDL 초기화 실패
    }

    m_bRunning = true;
    return true;
}

void Game::update()
{
    for (auto& go : m_gameObjects)
    {
        go->update();
    }
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //화면을 지움

    /*TheTextureManager::Instance()->draw("BG", 0, -2020 - m_playerY * 1.5, 640, 3840, 0, 0, m_pRenderer);
    TheTextureManager::Instance()->draw("Floor", 0, 1000 - m_playerY, 640, 385, 0, 0, m_pRenderer);
    TheTextureManager::Instance()->draw("Platform", 150, 800 - m_playerY, 140, 57, 0, 0, m_pRenderer);
    SDL_Delay(3);
    TheTextureManager::Instance()->draw("Player", m_playerX, m_playerY, 32, 32, m_playerFrame, m_playerHeight, m_pRenderer,playerFlip);*/
    for (auto& go : m_gameObjects)
    {
        go->draw(m_pRenderer);
    }

    SDL_RenderPresent(m_pRenderer); //화면을 그림 -> 백버퍼를 프론트 버퍼로
}

bool Game::running()
{
    return m_bRunning;
}

void Game::handleEvents()
{
    SDL_Event event;

    //사용자의 특정 신호의 입력 등 언제 발생할지 모르는 조건에 대해 반복할 때는 while문을 쓰는 것이 적합하다.
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_bRunning = false;
            break;
        }
    }
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    TheTextureManager::Instance()->destroyTexture("Player");
    TheTextureManager::Instance()->destroyTexture("Floor");
    TheTextureManager::Instance()->destroyTexture("BG");
    TheTextureManager::Instance()->destroyTexture("Platform");
    SDL_Quit();
}