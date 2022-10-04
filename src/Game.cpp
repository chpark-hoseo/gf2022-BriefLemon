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

        //���������� W(����), H(����) ���� ����
        SDL_QueryTexture(m_pTexture, NULL, NULL,
            &m_sourceRectangle.w, &m_sourceRectangle.h);

        //������, ���������� ����, ���� ���� ����, �������� ��ǥ ����
        //int textW, textH;
        int textX = 0, textY = 0;

        SDL_GetWindowSize(m_pWindow, &textX, &textY);   //������ â�� ����, ���� ���̸� ������

        //������, ���������� ��ǥ ��ġ ����
        m_sourceRectangle.x = 0;
        m_sourceRectangle.y = 0;

        m_destinationRectangle.x = 0;
        m_destinationRectangle.y = 0;
        
        //����,�������� ���� �ʺ� �����Ͽ� �Ϻκ� ȭ�鿡 ������
        m_destinationRectangle.w = m_sourceRectangle.w; 
        m_destinationRectangle.h = m_sourceRectangle.h;

        //�����ڰ� ȸ���� ���� ����
        rectPoint = {m_destinationRectangle.w, m_destinationRectangle.h};
    }
    else {
        return false; // SDL �ʱ�ȭ ����
    }

    m_bRunning = true;
    return true;
}

void Game::update()
{
    //���� �ֱ�� �׸��� ȸ��
    SDL_Delay(5);
    rectAngle++;

    //�� ������� ȸ���̵�
    m_destinationRectangle.x = cos(rectAngle / 15) * rectRadius + 320 - m_destinationRectangle.w;
    m_destinationRectangle.y = sin(rectAngle / 15) * rectRadius + 240 - m_destinationRectangle.h;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //ȭ���� ����
    SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, rectAngle, &rectPoint, SDL_FLIP_NONE); //����ۿ� ������
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
    SDL_Quit();
}