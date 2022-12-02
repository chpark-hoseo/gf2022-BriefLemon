#include "TileManager.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void TileManager::setGameObject(Player* player) {
    this->m_player = player;
}

void TileManager::init(int i) {
    std::srand((unsigned int)time(NULL));

    for (int x = 0; x < i - 1; x++) {
        Tile* tempTile = new Tile(new LoaderParams(0, 0, 100, 50, "Tile", 0, 0, SDL_FLIP_NONE));
        m_Tiles.push_back(tempTile);
    }

    for (auto& tiles : m_Tiles)
    {
        int tempX, tempY;
        tempX = std::rand() % (SCREEN_WIDTH - tiles->getWidth());
        tempY = std::rand() % (SCREEN_HEIGHT * 3 / i) + (SCREEN_HEIGHT * 3 / i * tileCount);
        tiles->init(tempX, tempY);

        tX[tileCount] = tempX;
        tY[tileCount] = tempY;

        tileCount++;
    }

}

void TileManager::draw() {
    for (auto& tiles : m_Tiles)
    {
        tiles->draw();
    }
}

void TileManager::update() {
    for (int i = 0; i < tileCount; i++)
    {
        if (!platformCheck(i)) continue;

        m_player->platformCheck(tY[i]);

         if (touchPlatform) {
             if (pX < tX[i] + tW && pX + pW  > tX[i]) {
                 //m_player->onFloor = true;
             }
             else {
                 touchPlatform = false;
                 m_player->onFloor = false;
             }
         }
    }
}

bool TileManager::platformCheck(int i) {
    pX = m_player->getXpos();
    pY = m_player->getYpos();
    pW = m_player->getWidth() - 10;
    pH = m_player->getHeight() - 15;
    tW = m_Tiles[i]->getWidth();
    tH = m_Tiles[i]->getHeight();

    if (pX + pW > tX[i] && pX < tX[i] + tW - 12) {
        if (pY + pH <= tY[i] + 20 && pY + pH > tY[i] - 10) {
            if (m_player->jumpHeight >= 0) {
                std::cout << pX << " , " << pY << " : " << tX[i] << " , " << tY[i] << std::endl;
                touchPlatform = true;
                return true;
            }
        }
    }
    return false;
}

TileManager* TileManager::s_pInstance = 0;