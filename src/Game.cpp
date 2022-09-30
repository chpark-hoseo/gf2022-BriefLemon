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

        //원본상자의 W(가로), H(세로) 길이 설정
        SDL_QueryTexture(m_pTexture, NULL, NULL,
            &m_sourceRectangle.w, &m_sourceRectangle.h);

        //대상상자, 원본상자의 가로, 세로 길이 설정, 대상상자의 좌표 설정
        int textW = 40, textH = 40;
        int srctextX = 50, srctextY = 50;
        int destextX = 80, destextY = 80;

        //대상상자, 원본상자의 좌표 위치 설정
        m_sourceRectangle.x = srctextX;
        m_sourceRectangle.y = srctextY;
        
        m_destinationRectangle.x = destextX;
        m_destinationRectangle.y = destextY;

        //원본,대상상자의 폭과 너비를 제한하여 일부분 화면에 렌더링
        m_destinationRectangle.w = m_sourceRectangle.w = textW; 
        m_destinationRectangle.h = m_sourceRectangle.h = textH;

    }
    else {
        return false; // SDL 초기화 실패
    }

    m_bRunning = true;
    return true;
}

void Game::update()
{

}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //화면을 지움
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
    SDL_Quit();
}