#include "Player.h"
#include "InputHandler.h"
#include <iostream>

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}

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
    std::cout << m_curFuel << std::endl;
    m_velocity.setY(m_gravity + jumpHeight);
    m_acceleration.setY(m_accelerator);

    if (m_position.getY() > 720 - 72) {
        m_position.setY(720 - 72);
        m_velocity.setY(0);
        onFloor = true;
    }

    if (isJump == true) {                                   //���� ������ ���
            m_accelerator = m_accelerator + 0.2;            //���ӵ� ���
            jumpHeight = jumpHeight + m_gravity;            //�������� ��� ����
            onFloor = false;
            if (jumpHeight > 0)
            {
                isJump = false;                             //�������� ����
                jumpHeight = -6;
            }
        }
    else {
        m_accelerator = m_accelerator + 0.2;
    }
}

void Player::handleInput() {

    //�¿� �̵�
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
        jumpHeight -= m_curFuel / (m_maxFuel / 15);   //�������̿� ���� �������� �Ϻθ� ����
        m_curFuel = 0;                              //������ �ʱ�ȭ
        isJump = true;                              //���� ���°� �ȴ�
        onFloor = false;                            //�ٴڿ��� �������ִ� ���°� �ȴ�
        m_accelerator = 0.0f;                          //���ӵ� �ʱ�ȭ
    }
}

bool AABB() {
    
}

void Player::clean() {}