#pragma once //헤더파일 중복, 순환참조, 중복정의를 방지하기 위해 사용한다./
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

	//키보드 변수
	const Uint8* Keyboard;

	//점프 관련 변수
	bool m_jumping = false;
	bool m_hitGround = false;
	double m_curJump = 0.0f;
	double m_jumpSpeed = 3.0f;
	double m_grav = -0.02f;
};