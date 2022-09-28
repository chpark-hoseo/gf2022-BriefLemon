#pragma once //헤더파일 중복, 순환참조, 중복정의를 방지하기 위해 사용한다./
#include <SDL2/SDL.h>

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
	SDL_Texture* m_bgTexture;
	SDL_Texture* m_tankTexture;

	// 원본 사각형
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_bgSourceRectangle;
	SDL_Rect m_tankSourceRectangle;

	// 대상 사각형
	SDL_Rect m_destinationRectangle;
	SDL_Rect m_bgDestinationRectangle;
	SDL_Rect m_tankDestinationRectangle;

	//Speed 방향 제어
	int rectDir = 1;
};
   