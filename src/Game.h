#pragma once //헤더파일 중복, 순환참조, 중복정의를 방지하기 위해 사용한다./
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

	SDL_Texture* m_pTexture;

	// 원본 사각형
	SDL_Rect m_sourceRectangle;

	// 대상 사각형
	SDL_Rect m_destinationRectangle;

	//애니메이션 속도 랜덤
	int randCount;

	//스프라이트 원 이동 함수
	double rectAngle = 0;
	const int rectRadius = 200;
};