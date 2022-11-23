#pragma once //헤더파일 중복, 순환참조, 중복정의를 방지하기 위해 사용한다./
#include "GameObject.h"
#include <vector>
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
private:
	Game() {}
	static Game* s_pInstance; // 정적 멤버변수

public:
	static Game* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
	SDL_Renderer* getRenderer() const { return m_pRenderer; }

	bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
	void render();
	void update();
	bool running();
	void handleEvents();
	void clean();
	void quit() { m_bRunning = false; }

private:
	std::vector<GameObject*> m_gameObjects;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
};

typedef Game TheGame;