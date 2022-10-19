#pragma once //헤더파일 중복, 순환참조, 중복정의를 방지하기 위해 사용한다./
#include "TextureManager.h"

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

	bool onFloor = false;
	double m_maxFuel = 500;
	double m_curFuel = 0;

	int m_playerX = 0;
	int m_playerY = 0;

	double gravity = 0.2;
	double accelerator1 = 0;
	double accelerator2 = 0;
	bool inJump = false;
	double jumpHeight = -10;

	bool isCharge = false;	//점프하고있는지 확인
	int m_currentFrame;		//애니메이션의 현재 프레임
	int m_currentHeight;	//2d 스프라이트 애니메이션의 현재 열(row)
};