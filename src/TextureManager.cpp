#include "TextureManager.h"

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    if (pTempSurface == 0) {
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);
    if (pTexture != 0) {
        m_textureMap[id] = pTexture;
        return true;
    }
    return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, int curFrame, int curHeight,
    SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0 + width * curFrame;
    srcRect.y = 0 + height * curHeight;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
    SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    int playerScreenY = m_player->getYpos();

    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y - SCREEN_HEIGHT * floorf((std::min(playerScreenY + m_player->getHeight(), SCREEN_HEIGHT * 2)) / SCREEN_HEIGHT);

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::destroyTexture(std::string id) {
    SDL_DestroyTexture(m_textureMap[id]);
}

void TextureManager::getGameObject(Player* player) {
    this->m_player = player;
}

TextureManager* TextureManager::s_pInstance = 0;