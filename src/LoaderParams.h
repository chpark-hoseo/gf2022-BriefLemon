#pragma once
#include <string>
#include <SDL2/SDL.h>

class LoaderParams {
public:
	LoaderParams(int x, int y, int width, int height, std::string textureID, int currentRow, int currentFrame, SDL_RendererFlip flip)
		:m_x(x),
		m_y(y),
		m_width(width),
		m_height(height),
		m_textureID(textureID),
		m_currentRow(currentRow),
		m_currentFrame(currentFrame),
		m_flip(flip) {}
	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string getTextureID() const { return m_textureID; }
	int getCurrentRow() const { return m_currentRow; }
	int getCurrentFrame() const { return m_currentFrame; }
	SDL_RendererFlip getFlip() const { return m_flip; }

private:
	int m_x, m_y;
	int m_width, m_height;
	std::string m_textureID;
	int m_currentRow, m_currentFrame;
	SDL_RendererFlip m_flip;
};