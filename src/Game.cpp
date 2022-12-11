#include "Game.h"
#include "Player.h"
#include "TileManager.h"
#include "ScreenManager.h"
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

        //Texture ����
        if (!TheTextureManager::Instance()->load("assets/StartScreen.png", "startScreen", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/StartButton.png", "startButton", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/ExitButton.png", "exitButton", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/ClearScreen.png", "clearScreen", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/Slime.png", "slime", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/starBG.png", "BG", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/Earth.png", "earth", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/RedPlanet.png", "redPlanet", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/Floor.png", "Floor", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/platform.png", "Tile", m_pRenderer)) { return false; }

        Player* player = new Player(new LoaderParams(100, 2304, 96, 72, "slime", 0, 0, SDL_FLIP_NONE));

        TheTextureManager::Instance()->getGameObject(player);

        TileManager::Instance()->init(player, 15);
        ScreenManager::Instance()->init(player, m_pRenderer);

        m_gameObjects.push_back(player);
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
    TileManager::Instance()->update();
    TheScreenManager::Instance()->update();
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //ȭ���� ����

    TheTextureManager::Instance()->drawFrame("BG", 0, 0, 640, 2304, 0, 0, m_pRenderer);
    TheTextureManager::Instance()->drawFrame("Floor", 0, 1921, 640, 383, 0, 0, m_pRenderer, SDL_FLIP_HORIZONTAL);
    TheTextureManager::Instance()->drawFrame("redPlanet", 300, 940, 708, 708, 0, 0, m_pRenderer);
    TheTextureManager::Instance()->drawFrame("earth", -600, 130, 894, 894, 0, 0, m_pRenderer, SDL_FLIP_VERTICAL);
    TileManager::Instance()->draw();
    for (auto& go : m_gameObjects)
    {
        go->draw();
    }
    TheScreenManager::Instance()->draw();

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
    for (auto& go : m_gameObjects)
    {
        go->clean();
    }
    TileManager::Instance()->clean();
    TheScreenManager::Instance()->clean();
    SDL_Quit();
}