#include "Game.h"
#include "Player.h"
#include "TileSpawner.h"
#include "InputHandler.h"

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

        //Texture 생성
        if (!TheTextureManager::Instance()->load("assets/Slime.png", "slime", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/starBG.png", "BG", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/Floor.png", "Floor", m_pRenderer)) { return false; }
        if (!TheTextureManager::Instance()->load("assets/platform.png", "Tile", m_pRenderer)) { return false; }

        Player* player = new Player(new LoaderParams(100, 2304, 96, 72, "slime", 0, 0, SDL_FLIP_NONE));

        Tile* tile = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile2 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile3 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile4 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile5 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile6 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile7 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile8 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile9 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile10 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile11 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile12 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile13 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile14 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile15 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile16 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile17 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile18 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile19 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        Tile* tile20 = new Tile(new LoaderParams(300, 2004, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));

        TheTextureManager::Instance()->getGameObject(player);

        TileSpawner::Instance()->setGameObject(player);

        TileSpawner::Instance()->m_Tiles.push_back(tile);
        TileSpawner::Instance()->m_Tiles.push_back(tile2);
        TileSpawner::Instance()->m_Tiles.push_back(tile3);
        TileSpawner::Instance()->m_Tiles.push_back(tile4);
        TileSpawner::Instance()->m_Tiles.push_back(tile5);
        TileSpawner::Instance()->m_Tiles.push_back(tile6);
        TileSpawner::Instance()->m_Tiles.push_back(tile7);
        TileSpawner::Instance()->m_Tiles.push_back(tile8);
        TileSpawner::Instance()->m_Tiles.push_back(tile9);
        TileSpawner::Instance()->m_Tiles.push_back(tile10);
        TileSpawner::Instance()->m_Tiles.push_back(tile11);
        TileSpawner::Instance()->m_Tiles.push_back(tile12);
        TileSpawner::Instance()->m_Tiles.push_back(tile13);
        TileSpawner::Instance()->m_Tiles.push_back(tile14);
        TileSpawner::Instance()->m_Tiles.push_back(tile15);
        TileSpawner::Instance()->m_Tiles.push_back(tile16);
        TileSpawner::Instance()->m_Tiles.push_back(tile17);
        TileSpawner::Instance()->m_Tiles.push_back(tile18);
        TileSpawner::Instance()->m_Tiles.push_back(tile19);
        TileSpawner::Instance()->m_Tiles.push_back(tile20);
        TileSpawner::Instance()->init();

        

        m_gameObjects.push_back(player);
        //m_gameObjects.push_back(tile);
        //m_gameObjects.push_back(tile2);
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

    TileSpawner::Instance()->update();
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //화면을 지움

    TheTextureManager::Instance()->drawFrame("BG", 0, 0, 640, 2304, 0, 0, m_pRenderer);
    TheTextureManager::Instance()->drawFrame("Floor", 0, 1921, 640, 383, 0, 0, m_pRenderer, SDL_FLIP_HORIZONTAL);
    TheTextureManager::Instance()->drawFrame("Floor", 0, 1153, 640, 383, 0, 0, m_pRenderer, SDL_FLIP_HORIZONTAL);
    TheTextureManager::Instance()->drawFrame("Floor", 0, 385, 640, 383, 0, 0, m_pRenderer, SDL_FLIP_VERTICAL);
    TileSpawner::Instance()->draw();
    for (auto& go : m_gameObjects)
    {
        go->draw();
    }
    

    SDL_RenderPresent(m_pRenderer); //화면을 그림 -> 백버퍼를 프론트 버퍼로
}

bool Game::running()
{
    return m_bRunning;
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();

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
    TheInputHandler::Instance()->clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    TheTextureManager::Instance()->destroyTexture("slime");
    TheTextureManager::Instance()->destroyTexture("Floor");
    TheTextureManager::Instance()->destroyTexture("BG");
    TheTextureManager::Instance()->destroyTexture("Platform");
    SDL_Quit();
}