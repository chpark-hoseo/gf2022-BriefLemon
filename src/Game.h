#pragma once //������� �ߺ�, ��ȯ����, �ߺ����Ǹ� �����ϱ� ���� ����Ѵ�./
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

	// ���� �簢��
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_bgSourceRectangle;
	SDL_Rect m_tankSourceRectangle;

	// ��� �簢��
	SDL_Rect m_destinationRectangle;
	SDL_Rect m_bgDestinationRectangle;
	SDL_Rect m_tankDestinationRectangle;

	//Speed ���� ����
	int rectDir = 1;
};
   