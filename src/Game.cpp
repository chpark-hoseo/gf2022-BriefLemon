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
        SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
        m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);

        pTempSurface = SDL_LoadBMP("assets/BG.bmp");
        m_bgTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);

        pTempSurface = SDL_LoadBMP("assets/Tank.bmp");
        m_tankTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);

        //원본상자의 W(가로), H(세로) 길이 설정
        SDL_QueryTexture(m_pTexture, NULL, NULL,
            &m_sourceRectangle.w, &m_sourceRectangle.h);
        SDL_QueryTexture(m_bgTexture, NULL, NULL,
            &m_bgSourceRectangle.w, &m_bgSourceRectangle.h);
        SDL_QueryTexture(m_tankTexture, NULL, NULL,
            &m_tankSourceRectangle.w, &m_tankSourceRectangle.h);

        //대상상자의 가로, 세로 길이를 원본상자의 길이로 설정
        m_destinationRectangle.w = m_sourceRectangle.w;
        m_destinationRectangle.h = m_sourceRectangle.h;

        m_bgDestinationRectangle.w = m_bgSourceRectangle.w;
        m_bgDestinationRectangle.h = m_bgSourceRectangle.h;

        m_tankDestinationRectangle.w = m_tankSourceRectangle.w;
        m_tankDestinationRectangle.h = m_tankSourceRectangle.h;

        //대상상자, 원본상자의 좌표 위치 설정
        m_destinationRectangle.x = m_sourceRectangle.x = 0;
        m_destinationRectangle.y = m_sourceRectangle.y = 0;

        m_bgDestinationRectangle.x = m_bgSourceRectangle.x = 0;
        m_bgDestinationRectangle.y = m_bgSourceRectangle.y = 0;

        m_tankDestinationRectangle.x = m_tankSourceRectangle.x = 0;
        m_tankDestinationRectangle.y = m_tankSourceRectangle.y = 0;

    }
    else {
        return false; // SDL 초기화 실패
    }

    m_bRunning = true;
    return true;
}

void Game::update()
{
    //윈도우 창 가로 길이 변수
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

    SDL_Delay(5); //이동딜레이 부여
    m_destinationRectangle.x += rectDir; //rectDir 만큼 이미지 이동
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //화면을 지움
    SDL_RenderCopy(m_pRenderer, m_bgTexture, &m_bgSourceRectangle, &m_bgDestinationRectangle);
    SDL_RenderCopy(m_pRenderer, m_tankTexture, &m_tankSourceRectangle, &m_tankDestinationRectangle);
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle); //백버퍼에 렌더링
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
        }
    }
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);

    //SDL_Texture 메모리에서 삭제
    SDL_DestroyTexture(m_pTexture);
    SDL_DestroyTexture(m_bgTexture);
    SDL_DestroyTexture(m_tankTexture);
    SDL_Quit();
}