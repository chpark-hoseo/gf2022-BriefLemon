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
    if (m_playerY > 720 - 150) {
        m_playerY = 720 - 150;
        onFloor = true;
    }
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //ȭ���� ����

    SDL_Delay(2);
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
                isCharge = true;
                break;
            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                isCharge = false;
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }
    }

    if (isCharge == true && onFloor == true) {
        if (m_curFuel <= m_maxFuel) {
            m_curFuel++;
        }
    }
    if(isCharge == false && onFloor == true) {
        if (m_curFuel > 0) {
            jumpHeight = -(6 + m_curFuel / 30);
            m_curFuel = 0;
            inJump = true;
            onFloor = false;
            accelerator1 = 0;
            accelerator2 = 0;
        }
    }

    if (inJump == true) {
        accelerator1 = accelerator1 + 0.015;
        accelerator2 = accelerator2 + 0.015;
        jumpHeight = jumpHeight + gravity;
        m_playerY = m_playerY + gravity + accelerator1 + accelerator2 + jumpHeight;
        if (jumpHeight > 0)
        {
            inJump = false;
            jumpHeight = -10;
        }
    }
    else {
        accelerator1 = accelerator1 + 0.015;
        accelerator2 = accelerator2 + 0.015;
        m_playerY = m_playerY + gravity + accelerator1 + accelerator2;
    }
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    TheTextureManager::Instance()->destroyTexture("Zelda");

    SDL_Quit();
}