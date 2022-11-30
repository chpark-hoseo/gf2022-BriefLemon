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

    /*if (m_playerHeight > 1) {
        m_playerFrame = 0;
    }
    else { m_playerFrame = ((SDL_GetTicks() / 100) % 4); }

    if (m_playerY > 720 - 50) {
        m_playerY = 720 - 50;
        onFloor = true;
    }*/

    //if (m_playerX < 0) { m_playerX = 0; }
    //if (m_playerX > 640 - 32) { m_playerX = 640 - 32; } //�÷��̾��� x��ġ ����

    //------------------------------------------------------------------------------------

    //SDL_Event event;

    //while (SDL_PollEvent(&event))
    //{
    //    switch (event.type)
    //    {
    //    case SDL_KEYDOWN:                           //Ű�� ��������
    //        switch (event.key.keysym.sym)
    //        {
    //        case SDLK_SPACE:
    //            if (onFloor) isCharge = true;       //�����̽��ٸ� �������� �ٴڿ� �־��ٸ� �������� ����
    //            break;

    //        case SDLK_LEFT:
    //            playerFlip = SDL_FLIP_HORIZONTAL;   //������ �������� �ִϸ��̼� �¿����
    //            break;

    //        case SDLK_RIGHT:
    //            playerFlip = SDL_FLIP_NONE;         //�������� �������� �ִϸ��̼� �������
    //            break;

    //        default:
    //            break;
    //        }
    //        break;

    //    case SDL_KEYUP:                             //Ű�� ������
    //        switch (event.key.keysym.sym)
    //        {
    //        case SDLK_SPACE:
    //            if (onFloor) isCharge = false;      //�����̽��ٸ� �������� �ٴڿ� �־��ٸ� �������� ����
    //            break;

    //        case SDLK_LEFT:
    //            m_playerHeight = 0;                 //������ Ű�� ������ �ִϸ��̼��� height�� 0���� �ٲ�
    //            break;

    //        case SDLK_RIGHT:
    //            m_playerHeight = 0;                 //���� Ű�� ������ �ִϸ��̼��� height�� 0���� �ٲ�
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
    //const Uint8* Keyboard = SDL_GetKeyboardState(NULL); //Ű���尪�� ����

    //if (isCharge != true) {
    //    if (Keyboard[SDL_SCANCODE_RIGHT])               //����� Ű���� ������ Ű�� �϶�
    //    {
    //        m_playerX += 1;                             //�÷��̾��� ��ġ�� ���������� �̵�
    //        m_playerHeight = 1;                         //�ִϸ��̼��� height�� 1�� �ٲ�     
    //    }
    //    if (Keyboard[SDL_SCANCODE_LEFT])                //����� Ű���� ���� Ű�� �϶�
    //    {
    //        m_playerX -= 1;                             //�÷��̾��� ��ġ�� �������� �̵�
    //        m_playerHeight = 1;                         //�ִϸ��̼��� height�� 1�� �ٲ�
    //    }
    //}

    //if (isCharge == true && onFloor == true) {          //���������̰� �ٴڿ� �ִ� ���¶��
    //    if (m_curFuel <= m_maxFuel) {
    //        m_curFuel++;                                //�������� �ִ� ������ ���ϰ����� ��� ������
    //    }

    //    m_playerHeight = 2;                             //�ִϸ��̼��� height�� 2�� �ٲ�
    //}
    //else if (isCharge == false && onFloor == true) {     //�������°� ������ �ٴڿ� �ִ� ���¶��
    //    if (m_curFuel > 0) {
    //        jumpHeight = -(3 + m_curFuel / (m_maxFuel / 10));   //�������̿� ���� �������� �Ϻθ� ����
    //        m_curFuel = 0;                              //������ �ʱ�ȭ
    //        inJump = true;                              //���� ���°� �ȴ�
    //        onFloor = false;                            //�ٴڿ��� �������ִ� ���°� �ȴ�
    //        accelerator1 = 0;                           //
    //        accelerator2 = 0;                           //���Ӱ� �ʱ�ȭ
    //    }
    //}

    //if (inJump == true) {                               //���� ������ ���
    //    accelerator1 = accelerator1 + 0.015;            //
    //    accelerator2 = accelerator2 + 0.015;            //���ӵ� ���
    //    jumpHeight = jumpHeight + gravity;              //�������� ��� ����
    //    m_playerY = m_playerY + gravity + accelerator1 + accelerator2 + jumpHeight; //�÷��̾��� y��ǥ�� ������
    //    m_playerHeight = 3;

    //    if (jumpHeight > 0)
    //    {
    //        inJump = false;                             //�������� ����
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

    //�¿� �̵�
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        m_velocity.setX(2);
        m_playerFrame = (SDL_GetTicks() / 150 % 4);
        m_flip = SDL_FLIP_HORIZONTAL;
    }
    else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        m_velocity.setX(-2);
        m_playerFrame = (SDL_GetTicks() / 150 % 4);
        m_flip = SDL_FLIP_NONE;
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
    else {
        jump();
    }

    //���� �̵�
    /*if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        m_velocity.setY(-2);
    }
    else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        m_velocity.setY(2);
    }
    else {
        m_velocity.setY(0);
    }*/


}

void Player::jump() {
    m_playerRow = 0;
    m_curFuel = 0;
}

void Player::clean() {}