#pragma once //������� �ߺ�, ��ȯ����, �ߺ����Ǹ� �����ϱ� ���� ����Ѵ�./
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"

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

	GameObject m_go;
	Player m_player;

	int m_currentFrame;		//�ִϸ��̼��� ���� ������
	int m_currentHeight;	//2d ��������Ʈ �ִϸ��̼��� ���� ��(row)
};