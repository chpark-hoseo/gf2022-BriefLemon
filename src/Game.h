#pragma once //������� �ߺ�, ��ȯ����, �ߺ����Ǹ� �����ϱ� ���� ����Ѵ�./
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"

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

	Monster m_monster1;
	Monster m_monster2;
	int m_m1Spd = 1;
	int m_m2Spd = 10;

	int m_currentFrame;		//�ִϸ��̼��� ���� ������
	int m_currentHeight;	//2d ��������Ʈ �ִϸ��̼��� ���� ��(row)
};