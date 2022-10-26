#include "Game.h"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        //������ ����
        m_pWindow = SDL_CreateWindow(
            title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if (m_pRenderer != 0) {
                SDL_SetRenderDrawColor(
                    m_pRenderer, 0, 0, 0, 255);
            }
            else {
                return false; // ������ ���� ����
            }
        }
        else {
            return false; // ������ ���� ����
        }

        //Texture ����
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
        return false; // SDL �ʱ�ȭ ����
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
    if (m_playerX > WINDOWWIDTH - 32) { m_playerX = WINDOWWIDTH - 32; } //�÷��̾��� x��ġ ����
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); //ȭ���� ����

    TheTextureManager::Instance()->draw("BG", 0, -2020 - m_playerY * 1.5, 640, 3840, 0, 0, m_pRenderer);
    TheTextureManager::Instance()->draw("Floor", 0, 1000 - m_playerY, 640, 385, 0, 0, m_pRenderer);
    TheTextureManager::Instance()->draw("Platform", 150, 800 - m_playerY, 140, 57, 0, 0, m_pRenderer);
    SDL_Delay(3);
    TheTextureManager::Instance()->draw("Player", m_playerX, m_playerY, 32, 32, m_playerFrame, m_playerHeight, m_pRenderer,playerFlip);

    SDL_RenderPresent(m_pRenderer); //ȭ���� �׸� -> ����۸� ����Ʈ ���۷�
}

bool Game::running()
{
    return m_bRunning;
}

void Game::handleEvents()
{
    SDL_Event event;

    //������� Ư�� ��ȣ�� �Է� �� ���� �߻����� �𸣴� ���ǿ� ���� �ݺ��� ���� while���� ���� ���� �����ϴ�.
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_bRunning = false;
            break;

        case SDL_KEYDOWN:                           //Ű�� ��������
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:                        
                if (onFloor) isCharge = true;       //�����̽��ٸ� �������� �ٴڿ� �־��ٸ� �������� ����
                break;

            case SDLK_LEFT:
                playerFlip = SDL_FLIP_HORIZONTAL;   //������ �������� �ִϸ��̼� �¿����
                break;

            case SDLK_RIGHT:
                playerFlip = SDL_FLIP_NONE;         //�������� �������� �ִϸ��̼� �������
                break;

            default:
                break;
            }
            break;

        case SDL_KEYUP:                             //Ű�� ������
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                if (onFloor) isCharge = false;      //�����̽��ٸ� �������� �ٴڿ� �־��ٸ� �������� ����
                break;

            case SDLK_LEFT:
                m_playerHeight = 0;                 //������ Ű�� ������ �ִϸ��̼��� height�� 0���� �ٲ�
                break;

            case SDLK_RIGHT:
                m_playerHeight = 0;                 //���� Ű�� ������ �ִϸ��̼��� height�� 0���� �ٲ�
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
    const Uint8* Keyboard = SDL_GetKeyboardState(NULL); //Ű���尪�� ����

    if (isCharge != true) {
        if (Keyboard[SDL_SCANCODE_RIGHT])               //����� Ű���� ������ Ű�� �϶�
        {
            m_playerX += 1;                             //�÷��̾��� ��ġ�� ���������� �̵�
            m_playerHeight = 1;                         //�ִϸ��̼��� height�� 1�� �ٲ�     
        }
        if (Keyboard[SDL_SCANCODE_LEFT])                //����� Ű���� ���� Ű�� �϶�
        {
            m_playerX -= 1;                             //�÷��̾��� ��ġ�� �������� �̵�
            m_playerHeight = 1;                         //�ִϸ��̼��� height�� 1�� �ٲ�
        }
    }

    if (isCharge == true && onFloor == true) {          //���������̰� �ٴڿ� �ִ� ���¶��
        if (m_curFuel <= m_maxFuel) {
            m_curFuel++;                                //�������� �ִ� ������ ���ϰ����� ��� ������
        }

        m_playerHeight = 2;                             //�ִϸ��̼��� height�� 2�� �ٲ�
    }
    else if(isCharge == false && onFloor == true) {     //�������°� ������ �ٴڿ� �ִ� ���¶��
        if (m_curFuel > 0) {
            jumpHeight = -(3 + m_curFuel / (m_maxFuel / 10));   //�������̿� ���� �������� �Ϻθ� ����
            m_curFuel = 0;                              //������ �ʱ�ȭ
            inJump = true;                              //���� ���°� �ȴ�
            onFloor = false;                            //�ٴڿ��� �������ִ� ���°� �ȴ�
            accelerator1 = 0;                           //
            accelerator2 = 0;                           //���Ӱ� �ʱ�ȭ
        }
    }

    if (inJump == true) {                               //���� ������ ���
        accelerator1 = accelerator1 + 0.015;            //
        accelerator2 = accelerator2 + 0.015;            //���ӵ� ���
        jumpHeight = jumpHeight + gravity;              //�������� ��� ����
        m_playerY = m_playerY + gravity + accelerator1 + accelerator2 + jumpHeight; //�÷��̾��� y��ǥ�� ������
        m_playerHeight = 3;

        if (jumpHeight > 0)
        {
            inJump = false;                             //�������� ����
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