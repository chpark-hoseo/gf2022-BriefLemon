#include "Game.h"

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
                    m_pRenderer, 0, 0, 160, 255);
            }
            else {
                return false; // ������ ���� ����
            }
        }
        else {
            return false; // ������ ���� ����
        }

        //Texture ����
        if (!TheTextureManager::Instance()->load("assets/Zelda.png", "Zelda", m_pRenderer))
        {
            return false;
        }

    }
    else {
        return false; // SDL �ʱ�ȭ ����
    }

    m_bRunning = true;
    return true;
}

void Game::update()
{
    if (m_playerY > 480 - 150) m_playerY = 480 - 150;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //ȭ���� ����

    SDL_Delay(3);
    TheTextureManager::Instance()->draw("Zelda", m_playerX, m_playerY, 104, 150, m_pRenderer);

    SDL_RenderPresent(m_pRenderer); //ȭ���� �׸� -> ����۸� ����Ʈ ���۷�
}

bool Game::running()
{
    return m_bRunning;
}

void Game::handleEvents()
{
    SDL_Event event;

    //������� Ư�� ��ȣ�� �Է� �� ���� �߻����� �𸣴� ���ǿ� ���� �ݺ��� ���� while���� ���� ���� �����ϴ�.
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_bRunning = false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                isJump = true;
                break;
            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                isJump = false;
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }
    }



    if (isJump) {
        m_curFuel--;
        m_playerY--;
    }
    else {
        m_playerY++;
    }
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    TheTextureManager::Instance()->destroyTexture("Zelda");

    SDL_Quit();
}