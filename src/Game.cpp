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
                    m_pRenderer, 0, 0, 160, 255);
            }
            else {
                return false; // 랜더러 생성 실패
            }
        }
        else {
            return false; // 윈도우 생성 실패
        }

        //Texture 생성
        GameObject* m_go = new GameObject();
        GameObject* m_player = new Player();
        GameObject* m_monster1 = new Monster();
        GameObject* m_monster2 = new Monster();

        if (!TheTextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer))
        {
            return false;
        }

        if (!TheTextureManager::Instance()->load("assets/Dogge.png", "dogge", m_pRenderer))
        {
            return false;
        }

        m_go->load(100, 100, 128, 82, "animate");
        m_player->load(300, 300, 128, 82, "animate");
        m_monster1->load(100, 300, 27, 31, "dogge");
        m_monster2->load(300, 100, 27, 31, "dogge");
        m_gameObjects.push_back(m_go);
        m_gameObjects.push_back(m_player);
        m_gameObjects.push_back(m_monster1);
        m_gameObjects.push_back(m_monster2);

    }
    else {
        return false; // SDL 초기화 실패
    }

    m_bRunning = true;
    return true;
}

void Game::update()
{
    for (auto &go : m_gameObjects)
    {
        go->update();
    }
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //화면을 지움
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
        default:
            break;
        }
    }
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    TheTextureManager::Instance()->destroyTexture("Zelda");

    SDL_Quit();
}