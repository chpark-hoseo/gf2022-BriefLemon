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
        SDL_Surface* pTempSurface = SDL_LoadBMP("assets/frogJump.bmp");
        m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);

        //원본상자의 W(가로), H(세로) 길이 설정
        m_sourceRectangle.w = 213;
        m_sourceRectangle.h = 104;

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
    //랜덤으로 애니메이션의 속도를 조절
    srand(time(NULL));  //랜덤 변수를 시간을 이용해 설정
    randCount = rand() % 3 + 1;

    m_sourceRectangle.x = 213 * ((SDL_GetTicks() * randCount / 100) % 6);   //스프라이트 원본상자의 좌표를 랜덤변수만큼의 배율로 조절

    //원 모양으로 스프라이트 이동
    rectAngle += 0.0001;

    //스프라이트의 좌표 설정
    m_destinationRectangle.x = cos(rectAngle) * rectRadius + 320 - m_destinationRectangle.w / 2;
    m_destinationRectangle.y = sin(rectAngle) * rectRadius + 240 - m_destinationRectangle.h / 2;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //화면을 지움
    SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, rectAngle * 60 + 90, NULL, SDL_FLIP_NONE); //스프라이트 회전
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