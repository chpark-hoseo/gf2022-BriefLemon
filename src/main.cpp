// SDL 
//
// written by changhoonpark@gmail.com

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <conio.h>

SDL_Window*		g_pWindow = 0;
SDL_Renderer*	g_pRenderer = 0;
bool g_bRunning = false; //프로그램이 Run 하고 있는지 여부
const int runTime = 10000; //프로그램 종료까지 시간(ms 단위)

int main(int argc, char* argv[])
{
	bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
	void render();

	if (init("Breaking Up HelloSDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_SHOWN))
	{
		g_bRunning = true;
	}
	else {
		return 1; //Something went wrong
	}

	while (g_bRunning) {
		//handle input - update - render
		render();

		if (SDL_GetTicks() > runTime) { //코드가 실행된 시간을 ms 단위로 표현
			g_bRunning = false;
		}
	}

	SDL_Quit();

	return 0;
}

bool init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		g_pWindow = SDL_CreateWindow(
			title, xpos, ypos, height, width, flags);

		if (g_pWindow != 0) {
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		}

	} else {
		return false;
	}

	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);

	return true;
}

void render()
{
	SDL_RenderClear(g_pRenderer);

	SDL_SetRenderDrawColor(g_pRenderer, rand() % 256, rand() % 256, rand() % 256, 255);
	SDL_Delay(1000);

	SDL_RenderPresent(g_pRenderer);
}