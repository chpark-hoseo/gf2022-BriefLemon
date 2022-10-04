#pragma once //������� �ߺ�, ��ȯ����, �ߺ����Ǹ� �����ϱ� ���� ����Ѵ�./
#include <SDL2/SDL.h>
//#include <stdlib.h>
//#include <time.h>
//#include <math.h>

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
	SDL_Texture* m_pTexture2;

	// ���� �簢��
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_sourceRectangle2;

	// ��� �簢��
	SDL_Rect m_destinationRectangle;
	SDL_Rect m_destinationRectangle2;
};