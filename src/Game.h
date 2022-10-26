#pragma once //������� �ߺ�, ��ȯ����, �ߺ����Ǹ� �����ϱ� ���� ����Ѵ�./
#include "TextureManager.h"

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 720

class Game
{
public:
	Game() { }
	~Game() { }

	bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
	void render();
	void update();
	bool running();
	void handleEvents();
	void clean();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	int m_playerX = 0;			//�÷��̾��� �ʱ�x��ǥ
	int m_playerY = 720 - 50;	//�÷��̾��� �ʱ�y��ǥ

	int m_playerFrame = 0;		//�÷��̾� ���� ������
	int m_playerHeight = 0;		//�÷��̾� 2d ��������Ʈ ������� (0 = idle. 1 = walk, 2 = charge, 3 = jump)
	SDL_RendererFlip playerFlip = SDL_FLIP_NONE;

	bool onFloor = false;		//�ٴڿ� �浹������ üũ
	double m_maxFuel = 150;		//�ִ� ���� ��������
	double m_curFuel = 0;		//���� ���� ��������
	double gravity = 0.2;		//�߷°� ����
	double accelerator1 = 0;	//���ӷ� ����-1
	double accelerator2 = 0;	//���ӷ� ����-2
	bool inJump = false;		//���� �ϰ��ִ� �������� Ȯ��
	double jumpHeight = -3;	//�⺻ ���� ���� ����

	bool isCharge = false;		//������(�����̽��� ���� Ȯ��)���� Ȯ��
};