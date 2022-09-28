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
        SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
        m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);

        pTempSurface = SDL_LoadBMP("assets/BG.bmp");
        m_bgTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);

        pTempSurface = SDL_LoadBMP("assets/Tank.bmp");
        m_tankTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);

        //���������� W(����), H(����) ���� ����
        SDL_QueryTexture(m_pTexture, NULL, NULL,
            &m_sourceRectangle.w, &m_sourceRectangle.h);
        SDL_QueryTexture(m_bgTexture, NULL, NULL,
            &m_bgSourceRectangle.w, &m_bgSourceRectangle.h);
        SDL_QueryTexture(m_tankTexture, NULL, NULL,
            &m_tankSourceRectangle.w, &m_tankSourceRectangle.h);

        //�������� ����, ���� ���̸� ���������� ���̷� ����
        m_destinationRectangle.w = m_sourceRectangle.w;
        m_destinationRectangle.h = m_sourceRectangle.h;

        m_bgDestinationRectangle.w = m_bgSourceRectangle.w;
        m_bgDestinationRectangle.h = m_bgSourceRectangle.h;

        m_tankDestinationRectangle.w = m_tankSourceRectangle.w;
        m_tankDestinationRectangle.h = m_tankSourceRectangle.h;

        //������, ���������� ��ǥ ��ġ ����
        m_destinationRectangle.x = m_sourceRectangle.x = 0;
        m_destinationRectangle.y = m_sourceRectangle.y = 0;

        m_bgDestinationRectangle.x = m_bgSourceRectangle.x = 0;
        m_bgDestinationRectangle.y = m_bgSourceRectangle.y = 0;

        m_tankDestinationRectangle.x = m_tankSourceRectangle.x = 0;
        m_tankDestinationRectangle.y = m_tankSourceRectangle.y = 0;

    }
    else {
        return false; // SDL �ʱ�ȭ ����
    }

    m_bRunning = true;
    return true;
}

void Game::update()
{
    //������ â ���� ���� ����
    int windowWidth;
    SDL_GetWindowSize(m_pWindow, &windowWidth, NULL);

    if (m_destinationRectangle.x > windowWidth - m_destinationRectangle.w)
    {
        rectDir = -1;
    }
    else if (m_destinationRectangle.x < 0)
    {
        rectDir = 1;
    }

    SDL_Delay(5); //�̵������� �ο�
    m_destinationRectangle.x += rectDir; //rectDir ��ŭ �̹��� �̵�
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //ȭ���� ����
    SDL_RenderCopy(m_pRenderer, m_bgTexture, &m_bgSourceRectangle, &m_bgDestinationRectangle);
    SDL_RenderCopy(m_pRenderer, m_tankTexture, &m_tankSourceRectangle, &m_tankDestinationRectangle);
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle); //����ۿ� ������
    SDL_RenderPresent(m_pRenderer); //ȭ���� �׸� -> ����۸� ����Ʈ ���۷�?
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
        default:
            break;
        }
    }
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);

    //SDL_Texture �޸𸮿��� ����
    SDL_DestroyTexture(m_pTexture);
    SDL_DestroyTexture(m_bgTexture);
    SDL_DestroyTexture(m_tankTexture);
    SDL_Quit();
}