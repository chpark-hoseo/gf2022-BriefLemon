#include "Game.h"
#include "Player.h"
#include "Tile.h"
#include "ColliderManager.h"
#include "InputHandler.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        //������ ����
        m_pWindow = SDL_CreateWindow(
            title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if (m_pRenderer != 0) {
                SDL_SetRenderDrawColor(
                    m_pRenderer, 0, 0, 0, 255);
            }
            else {
                return false; // ������ ���� ����
            }
        }
        else {
            return false; // ������ ���� ����
        }

        Player* player = new Player(new LoaderParams(100, 600, 96, 72, "slime", 0, 0, SDL_FLIP_NONE));
        Tile* tile = new Tile(new LoaderParams(300, 200, 140, 57, "Tile", 0, 0, SDL_FLIP_NONE));

        //Texture ����
        if (!TheTextureManager::Instance()->load("assets/Slime.png", "slime", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/starBG.png", "BG", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/Floor.png", "Floor", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/platform.png", "Tile", m_pRenderer)) { return false; }

        TheCollider::instance()->setGameObject(player, tile);

        m_gameObjects.push_back(player);
        m_gameObjects.push_back(tile);
    }
    else {
        return false; // SDL �ʱ�ȭ ����
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

    TheCollider::instance()->update();
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //ȭ���� ����

    for (auto& go : m_gameObjects)
    {
        go->draw();
    }

    SDL_RenderPresent(m_pRenderer); //ȭ���� �׸� -> ����۸� ����Ʈ ���۷�
}

bool Game::running()
{
    return m_bRunning;
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();

    SDL_Event event;

    //������� Ư�� ��ȣ�� �Է� �� ���� �߻����� �𸣴� ���ǿ� ���� �ݺ��� ���� while���� ���� ���� �����ϴ�.
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
    TheInputHandler::Instance()->clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    TheTextureManager::Instance()->destroyTexture("slime");
    TheTextureManager::Instance()->destroyTexture("Floor");
    TheTextureManager::Instance()->destroyTexture("BG");
    TheTextureManager::Instance()->destroyTexture("Platform");
    SDL_Quit();
}