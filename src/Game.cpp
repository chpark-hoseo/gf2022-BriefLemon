#include "Game.h"

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
                    m_pRenderer, 0, 0, 150, 255);
            }
            else {
                return false; // 랜더러 생성 실패
            }
        }
        else {
            return false; // 윈도우 생성 실패
        }

        //Texture 생성
        SDL_Surface* pTempSurface = IMG_Load("assets/frogjump.bmp");
        m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);

        //원본상자의 W(가로), H(세로) 길이 설정
        m_sourceRectangle.w = 213;
        m_sourceRectangle.h = 103;

        //대상상자, 원본상자의 좌표 위치 설정
        m_sourceRectangle.x = m_destinationRectangle.x = 0;
        m_sourceRectangle.y = m_destinationRectangle.y = 0;

        //대상상자의 크기(w,h)를 원본상자와 동일하게 설정
        m_destinationRectangle.w = m_sourceRectangle.w;
        m_destinationRectangle.h = m_sourceRectangle.h;

    }
    else {
        return false; // SDL 초기화 실패
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
    SDL_RenderClear(m_pRenderer); //화면을 지움
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle); //백버퍼에 스프라이트 그림
    SDL_RenderPresent(m_pRenderer); //화면을 그림 -> 백버퍼를 프론트 버퍼로?
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

    //SDL_Texture 메모리에서 삭제
    SDL_DestroyTexture(m_pTexture);
    SDL_Quit();
}