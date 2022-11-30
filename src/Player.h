#pragma once
#include "SDLGameObject.h"
#include <SDL2/SDL.h>

class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
    virtual void draw();
	virtual void update();
	virtual void clean();
	void handleInput();

	void jump();

	int m_playerRow = 0;		//�÷��̾� 2d ��������Ʈ ������� (0 = idle. 1 = walk, 2 = charge, 3 = jump)
	int m_playerFrame = 0;		//�÷��̾� ���� ������
	
	const int m_maxFuel = 100;		//�ִ� ���� ��������
	int m_curFuel = 0;		//���� ���� ��������

	const double gravity = 0.2;		//�߷°� ����
	double accelerator1 = 0;	//���ӷ� ����-1
	double accelerator2 = 0;	//���ӷ� ����-2

	double jumpHeight = 3;	//�⺻ ���� ���� ����

	bool isJump = false;		//���� �ϰ��ִ� �������� Ȯ��
	bool onFloor = false;		//�ٴڿ� �浹������ üũ
	bool isCharge = false;		//������(�����̽��� ���� Ȯ��)���� Ȯ��
};