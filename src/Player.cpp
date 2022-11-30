#include "Player.h"
#include "InputHandler.h"
#include <iostream>

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}

int Player::getXpos() {
    return m_position.getX();
}
int Player::getYpos() {
    return m_position.getY();
}

void Player::draw()
{
    SDLGameObject::draw();
    m_currentFrame = m_playerFrame;
    m_currentRow = m_playerRow;
}

void Player::update()
{
    handleInput();
    SDLGameObject::update();

    m_velocity.setY(m_gravity + jumpHeight);
    m_acceleration.setY(m_accelerator);

    if (m_position.getY() > 720 - 72) {
        m_position.setY(720 - 72);
        m_velocity.setY(0);
        onFloor = true;
    }

    if (isJump == true) {                                   //점프 상태일 경우
            m_accelerator = m_accelerator + 0.2;            //가속도 상승
            jumpHeight = jumpHeight + m_gravity;            //점프높이 계속 감소
            onFloor = false;

            if (m_position.getX() < 0) {
                m_velocity.setX(-m_velocity.getX());
            }
            if (m_position.getX() > 640 - m_width) {
                m_velocity.setX(-m_velocity.getX());
            }

            if (jumpHeight > 0)
            {
                isJump = false;                             //점프상태 해제
                m_curFuel = 0;                              //충전값 초기화
                jumpHeight = -6;
            }
        }
    else {
        m_accelerator = m_accelerator + 0.2;
        if (m_position.getX() < 0) m_position.setX(0);
        if (m_position.getX() > 640 - m_width) m_position.setX(640 - m_width);
    }
}

void Player::handleInput() {

    //좌우 이동
    if (onFloor) {
        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
            m_playerRow = 0;
            m_playerFrame = (SDL_GetTicks() / 150 % 4);
            m_flip = SDL_FLIP_HORIZONTAL;

            m_velocity.setX(4);
        }
        else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
            m_playerRow = 0;
            m_playerFrame = (SDL_GetTicks() / 150 % 4);
            m_flip = SDL_FLIP_NONE;

            m_velocity.setX(-4);
        }
        else {
            m_playerFrame = 0;

            m_velocity.setX(0);
        }

        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
            m_playerRow = 1;
            m_playerFrame = (SDL_GetTicks() / 150 % 2);
            m_velocity.setX(0);

            if (m_curFuel < m_maxFuel) {
                m_curFuel++;
            }
        }
        else
        {
            jump();
        }
    }
}

void Player::jump() {
    if (m_curFuel > 0 && onFloor) {
        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) m_velocity.setX(m_curFuel / 15);
        else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) m_velocity.setX(-m_curFuel / 15);
        else m_velocity.setX(0);

        jumpHeight -= m_curFuel / (m_maxFuel / 15);   //점프높이에 현재 충전값의 일부를 더함
        isJump = true;                              //점프 상태가 된다
        onFloor = false;                            //바닥에서 떨어져있는 상태가 된다
        m_accelerator = 0.0f;                          //가속도 초기화
    }
}

bool AABB() {
    return true;
}

void Player::clean() {}