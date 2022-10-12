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
                    m_pRenderer, 0, 0, 150, 255);
            }
            else {
                return false; // ������ ���� ����
            }
        }
        else {
            return false; // ������ ���� ����
        }

        //Texture ����
        SDL_Surface* pTempSurface = IMG_Load("assets/frogjump.bmp");
        m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);

        //���������� W(����), H(����) ���� ����
        m_sourceRectangle.w = 213;
        m_sourceRectangle.h = 103;

        //������, ���������� ��ǥ ��ġ ����
        m_sourceRectangle.x = m_destinationRectangle.x = 0;
        m_sourceRectangle.y = m_destinationRectangle.y = 0;

        //�������� ũ��(w,h)�� �������ڿ� �����ϰ� ����
        m_destinationRectangle.w = m_sourceRectangle.w;
        m_destinationRectangle.h = m_sourceRectangle.h;

    }
    else {
        return false; // SDL �ʱ�ȭ ����
    }

    m_bRunning = true;
    return true;
}

void Game::update()
{
    m_destinationRectangle.y += 1;

    if (m_destinationRectangle.y > 480 - m_destinationRectangle.h) { m_destinationRectangle.y = 480 - m_destinationRectangle.h;  m_hitGround = true; }
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //ȭ���� ����
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle); //����ۿ� ��������Ʈ �׸�
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

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    if (m_hitGround) {
                        m_hitGround = false;
                        m_jumping = true;
                        m_curJump = m_jumpSpeed;
                    }
                    break;
                }

                break;
        }
    }

    SDL_PumpEvents();
    Keyboard = SDL_GetKeyboardState(NULL);

    if (Keyboard[SDL_SCANCODE_RIGHT])
    {
        SDL_Delay(3);
        m_destinationRectangle.x += 1;
    }
    if (Keyboard[SDL_SCANCODE_LEFT])
    {
        SDL_Delay(3);
        m_destinationRectangle.x -= 1;
    }

    if (m_jumping) {
        SDL_Delay(3);
        m_destinationRectangle.y -= m_curJump;
        m_curJump += m_grav;

        if (m_curJump > 3.0f) { m_curJump = 3.0f; }
        if (m_curJump < -3.0f) { m_curJump = -3.0f; }
\
        if (m_hitGround) {
            m_jumping = false;
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