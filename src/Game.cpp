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
        if (!TheTextureManager::Instance()->load("assets/Player.png", "Player", m_pRenderer))
        {
            return false;
        }

        if (!TheTextureManager::Instance()->load("assets/starBG.png", "BG", m_pRenderer))
        {
            return false;
        }

        if (!TheTextureManager::Instance()->load("assets/Floor.png", "Floor", m_pRenderer))
        {
            return false;
        }

        if (!TheTextureManager::Instance()->load("assets/platform.png", "Platform", m_pRenderer))
        {
            return false;
        }

    }
    else {
        return false; // SDL 초기화 실패
    }

    m_bRunning = true;
    return true;
}

void Game::update()
{
    if (m_playerHeight > 1) {
        m_playerFrame = 0;
    }
    else { m_playerFrame = ((SDL_GetTicks() / 100) % 4); }

    if (m_playerY > 720 - 50) {
        m_playerY = 720 - 50;
        onFloor = true;
    }

    if (m_playerX < 0) { m_playerX = 0; }
    if (m_playerX > WINDOWWIDTH - 32) { m_playerX = WINDOWWIDTH - 32; } //플레이어의 x위치 조절
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //화면을 지움

    TheTextureManager::Instance()->draw("BG", 0, -2020 - m_playerY * 1.5, 640, 3840, 0, 0, m_pRenderer);
    TheTextureManager::Instance()->draw("Floor", 0, 1000 - m_playerY, 640, 385, 0, 0, m_pRenderer);
    TheTextureManager::Instance()->draw("Platform", 150, 800 - m_playerY, 140, 57, 0, 0, m_pRenderer);
    SDL_Delay(3);
    TheTextureManager::Instance()->draw("Player", m_playerX, m_playerY, 32, 32, m_playerFrame, m_playerHeight, m_pRenderer,playerFlip);

    SDL_RenderPresent(m_pRenderer); //화면을 그림 -> 백버퍼를 프론트 버퍼로
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

        case SDL_KEYDOWN:                           //키를 눌렀을때
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:                        
                if (onFloor) isCharge = true;       //스페이스바를 눌렀을때 바닥에 있었다면 충전상태 시작
                break;

            case SDLK_LEFT:
                playerFlip = SDL_FLIP_HORIZONTAL;   //왼쪽을 눌렀을때 애니메이션 좌우반전
                break;

            case SDLK_RIGHT:
                playerFlip = SDL_FLIP_NONE;         //오른쪽을 눌렀을때 애니메이션 원래대로
                break;

            default:
                break;
            }
            break;

        case SDL_KEYUP:                             //키를 뗏을때
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                if (onFloor) isCharge = false;      //스페이스바를 눌렀을때 바닥에 있었다면 충전상태 해제
                break;

            case SDLK_LEFT:
                m_playerHeight = 0;                 //오른쪽 키를 뗐을때 애니메이션의 height를 0으로 바꿈
                break;

            case SDLK_RIGHT:
                m_playerHeight = 0;                 //왼쪽 키를 뗐을때 애니메이션의 height를 0으로 바꿈
                break;

            default:
                break;
            }
            break;

        default:
            break;
        }
    }

    SDL_PumpEvents();
    const Uint8* Keyboard = SDL_GetKeyboardState(NULL); //키보드값을 저장

    if (isCharge != true) {
        if (Keyboard[SDL_SCANCODE_RIGHT])               //저장된 키값이 오른쪽 키값 일때
        {
            m_playerX += 1;                             //플레이어의 위치를 오른쪽으로 이동
            m_playerHeight = 1;                         //애니메이션의 height를 1로 바꿈     
        }
        if (Keyboard[SDL_SCANCODE_LEFT])                //저장된 키값이 왼쪽 키값 일때
        {
            m_playerX -= 1;                             //플레이어의 위치를 왼쪽으로 이동
            m_playerHeight = 1;                         //애니메이션의 height를 1로 바꿈
        }
    }

    if (isCharge == true && onFloor == true) {          //충전상태이고 바닥에 있는 상태라면
        if (m_curFuel <= m_maxFuel) {
            m_curFuel++;                                //충전값을 최대 충전값 이하값으로 계속 더해짐
        }

        m_playerHeight = 2;                             //애니메이션의 height를 2로 바꿈
    }
    else if(isCharge == false && onFloor == true) {     //충전상태가 끝났고 바닥에 있는 상태라면
        if (m_curFuel > 0) {
            jumpHeight = -(3 + m_curFuel / (m_maxFuel / 10));   //점프높이에 현재 충전값의 일부를 더함
            m_curFuel = 0;                              //충전값 초기화
            inJump = true;                              //점프 상태가 된다
            onFloor = false;                            //바닥에서 떨어져있는 상태가 된다
            accelerator1 = 0;                           //
            accelerator2 = 0;                           //가속값 초기화
        }
    }

    if (inJump == true) {                               //점프 상태일 경우
        accelerator1 = accelerator1 + 0.015;            //
        accelerator2 = accelerator2 + 0.015;            //가속도 상승
        jumpHeight = jumpHeight + gravity;              //점프높이 계속 감소
        m_playerY = m_playerY + gravity + accelerator1 + accelerator2 + jumpHeight; //플레이어의 y좌표를 조절함
        m_playerHeight = 3;

        if (jumpHeight > 0)
        {
            inJump = false;                             //점프상태 해제
            jumpHeight = -6;
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
    TheTextureManager::Instance()->destroyTexture("Player");
    TheTextureManager::Instance()->destroyTexture("Floor");
    TheTextureManager::Instance()->destroyTexture("BG");
    TheTextureManager::Instance()->destroyTexture("Platform");
    SDL_Quit();
}