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
int Player::getWidth() {
    return m_width;
}
int Player::getHeight() {
    return m_height;
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
    curSpeed = m_velocity.getY();

    if (onFloor) {
        m_velocity.setY(0);
        jumpSpeed = 0;
        isJump = false;
    }
    else {
        m_currentRow = 2;
        m_currentFrame = 0;
        m_velocity.setY(jumpSpeed);
        m_acceleration.setY(m_accelerator);
    }

    if (m_position.getY() > SCREEN_HEIGHT * GAME_HEIGHT - m_height) {
        m_position.setY(SCREEN_HEIGHT * GAME_HEIGHT - m_height);
        onFloor = true;
    }

    if (isJump == true) {                                   //���� ������ ���
            m_accelerator = m_accelerator + m_accelPlus;            //���ӵ� ���
            jumpSpeed = jumpSpeed + m_gravity;            //�������� ��� ����
            m_curFuel = 0;                                  //������ �ʱ�ȭ
            onFloor = false;

            if (m_position.getX() < 0) {
                m_velocity.setX(-m_velocity.getX());
            }
            if (m_position.getX() > 640 - m_width) {
                m_velocity.setX(-m_velocity.getX());
            }

            if (jumpSpeed > 0)
            {
                isJump = false;                             //�������� ����
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
            m_playerRow = 0;
            m_playerFrame = 3;

            m_velocity.setX(0);
        }

        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
            m_playerRow = 1;
            m_playerFrame = 1;
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

        jumpSpeed -= 6 + m_curFuel / (m_maxFuel / 15);   //�������̿� ���� �������� �Ϻθ� ����
        isJump = true;                                  //���� ���°� �ȴ�
        onFloor = false;                                //�ٴڿ��� �������ִ� ���°� �ȴ�
        m_position.setY(m_position.getY() - 15);
        m_accelerator = 0.0f;                          //���ӵ� �ʱ�ȭ
    }
}

void Player::platformCheck(int tY) {
    if (m_position.getY() > tY - m_height + 15) {
        m_position.setY(tY - m_height + 15);
        onFloor = true;
    }
}

void Player::clean() {}