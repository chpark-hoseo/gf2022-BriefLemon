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

    if (isJump == true) {                                   //���� ������ ���
            m_accelerator = m_accelerator + 0.2;            //���ӵ� ���
            jumpHeight = jumpHeight + m_gravity;            //�������� ��� ����
            onFloor = false;

            if (m_position.getX() < 0) {
                m_velocity.setX(-m_velocity.getX());
            }
            if (m_position.getX() > 640 - m_width) {
                m_velocity.setX(-m_velocity.getX());
            }

            if (jumpHeight > 0)
            {
                isJump = false;                             //�������� ����
                m_curFuel = 0;                              //������ �ʱ�ȭ
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
        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) m_velocity.setX(m_curFuel / 15);
        else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) m_velocity.setX(-m_curFuel / 15);
        else m_velocity.setX(0);

        jumpHeight -= m_curFuel / (m_maxFuel / 15);   //�������̿� ���� �������� �Ϻθ� ����
        isJump = true;                              //���� ���°� �ȴ�
        onFloor = false;                            //�ٴڿ��� �������ִ� ���°� �ȴ�
        m_accelerator = 0.0f;                          //���ӵ� �ʱ�ȭ
    }
}

bool AABB() {
    return true;
}

void Player::clean() {}