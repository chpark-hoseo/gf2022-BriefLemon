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

	int getXpos();
	int getYpos();
	int getWidth();
	int getHeight();

	void platformCheck(int tY);

private:
	void jump();

	int m_playerRow = 0;		//�÷��̾� 2d ��������Ʈ ������� (0 = idle. 1 = walk, 2 = charge, 3 = jump)
	int m_playerFrame = 0;		//�÷��̾� ���� ������
	
	const int m_maxFuel = 100;		//�ִ� ���� ��������
	int m_curFuel = 0;		//���� ���� ��������

	const float m_gravity = 0.2f;		//�߷°� ����
	float m_accelerator = 0.0f;	//���ӷ� ����-1
	float accelerator2 = 0.0f;	//���ӷ� ����-2

	float jumpHeight = 0.0f;	//�⺻ ���� ���� ����

	bool isJump = false;		//���� �ϰ��ִ� �������� Ȯ��
	bool onFloor = false;		//�ٴڿ� �浹������ üũ
};