#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    handleInput();
    SDLGameObject::update();
    /*if (m_playerHeight > 1) {
        m_playerFrame = 0;
    }
    else { m_playerFrame = ((SDL_GetTicks() / 100) % 4); }

    if (m_playerY > 720 - 50) {
        m_playerY = 720 - 50;
        onFloor = true;
    }*/

    //if (m_playerX < 0) { m_playerX = 0; }
    //if (m_playerX > 640 - 32) { m_playerX = 640 - 32; } //플레이어의 x위치 조절

    //------------------------------------------------------------------------------------

    //SDL_Event event;

    //while (SDL_PollEvent(&event))
    //{
    //    switch (event.type)
    //    {
    //    case SDL_KEYDOWN:                           //키를 눌렀을때
    //        switch (event.key.keysym.sym)
    //        {
    //        case SDLK_SPACE:
    //            if (onFloor) isCharge = true;       //스페이스바를 눌렀을때 바닥에 있었다면 충전상태 시작
    //            break;

    //        case SDLK_LEFT:
    //            playerFlip = SDL_FLIP_HORIZONTAL;   //왼쪽을 눌렀을때 애니메이션 좌우반전
    //            break;

    //        case SDLK_RIGHT:
    //            playerFlip = SDL_FLIP_NONE;         //오른쪽을 눌렀을때 애니메이션 원래대로
    //            break;

    //        default:
    //            break;
    //        }
    //        break;

    //    case SDL_KEYUP:                             //키를 뗏을때
    //        switch (event.key.keysym.sym)
    //        {
    //        case SDLK_SPACE:
    //            if (onFloor) isCharge = false;      //스페이스바를 눌렀을때 바닥에 있었다면 충전상태 해제
    //            break;

    //        case SDLK_LEFT:
    //            m_playerHeight = 0;                 //오른쪽 키를 뗐을때 애니메이션의 height를 0으로 바꿈
    //            break;

    //        case SDLK_RIGHT:
    //            m_playerHeight = 0;                 //왼쪽 키를 뗐을때 애니메이션의 height를 0으로 바꿈
    //            break;

    //        default:
    //            break;
    //        }
    //        break;

    //    default:
    //        break;
    //    }
    //}

    //SDL_PumpEvents();
    //const Uint8* Keyboard = SDL_GetKeyboardState(NULL); //키보드값을 저장

    //if (isCharge != true) {
    //    if (Keyboard[SDL_SCANCODE_RIGHT])               //저장된 키값이 오른쪽 키값 일때
    //    {
    //        m_playerX += 1;                             //플레이어의 위치를 오른쪽으로 이동
    //        m_playerHeight = 1;                         //애니메이션의 height를 1로 바꿈     
    //    }
    //    if (Keyboard[SDL_SCANCODE_LEFT])                //저장된 키값이 왼쪽 키값 일때
    //    {
    //        m_playerX -= 1;                             //플레이어의 위치를 왼쪽으로 이동
    //        m_playerHeight = 1;                         //애니메이션의 height를 1로 바꿈
    //    }
    //}

    //if (isCharge == true && onFloor == true) {          //충전상태이고 바닥에 있는 상태라면
    //    if (m_curFuel <= m_maxFuel) {
    //        m_curFuel++;                                //충전값을 최대 충전값 이하값으로 계속 더해짐
    //    }

    //    m_playerHeight = 2;                             //애니메이션의 height를 2로 바꿈
    //}
    //else if (isCharge == false && onFloor == true) {     //충전상태가 끝났고 바닥에 있는 상태라면
    //    if (m_curFuel > 0) {
    //        jumpHeight = -(3 + m_curFuel / (m_maxFuel / 10));   //점프높이에 현재 충전값의 일부를 더함
    //        m_curFuel = 0;                              //충전값 초기화
    //        inJump = true;                              //점프 상태가 된다
    //        onFloor = false;                            //바닥에서 떨어져있는 상태가 된다
    //        accelerator1 = 0;                           //
    //        accelerator2 = 0;                           //가속값 초기화
    //    }
    //}

    //if (inJump == true) {                               //점프 상태일 경우
    //    accelerator1 = accelerator1 + 0.015;            //
    //    accelerator2 = accelerator2 + 0.015;            //가속도 상승
    //    jumpHeight = jumpHeight + gravity;              //점프높이 계속 감소
    //    m_playerY = m_playerY + gravity + accelerator1 + accelerator2 + jumpHeight; //플레이어의 y좌표를 조절함
    //    m_playerHeight = 3;

    //    if (jumpHeight > 0)
    //    {
    //        inJump = false;                             //점프상태 해제
    //        jumpHeight = -6;
    //    }
    //}
    //else {
    //    accelerator1 = accelerator1 + 0.015;
    //    accelerator2 = accelerator2 + 0.015;
    //    m_playerY = m_playerY + gravity + accelerator1 + accelerator2;
    //}

}

void Player::handleInput() {
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        m_velocity.setX(2);
    }
    else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        m_velocity.setX(-2);
    }
    else {
        m_velocity.setX(0);
    }

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        m_velocity.setY(-2);
    }
    else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        m_velocity.setY(2);
    }
    else {
        m_velocity.setY(0);
    }
}

void Player::clean() {}