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

	int m_playerRow = 0;		//플레이어 2d 스프라이트 현재높이 (0 = idle. 1 = walk, 2 = charge, 3 = jump)
	int m_playerFrame = 0;		//플레이어 현재 프레임
	
	const int m_maxFuel = 100;		//최대 점프 충전상태
	int m_curFuel = 0;		//현재 점프 충전상태

	const float m_gravity = 0.2f;		//중력값 설정
	float m_accelerator = 0.0f;	//가속력 설정-1
	float accelerator2 = 0.0f;	//가속력 설정-2

	float jumpHeight = 0.0f;	//기본 점프 높이 설정

	bool isJump = false;		//점프 하고있는 상태인지 확인
	bool onFloor = false;		//바닥에 충돌중인지 체크
};