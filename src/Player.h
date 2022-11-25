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

	int m_playerRow = 0;		//�÷��̾� 2d ��������Ʈ ������� (0 = idle. 1 = walk, 2 = charge, 3 = jump)
	int m_playerFrame = 0;		//�÷��̾� ���� ������

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