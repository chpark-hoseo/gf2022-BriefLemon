#include "TileSpawner.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void TileSpawner::setGameObject(Player* player) {
    this->m_player = player;
}

void TileSpawner::init() {
    std::srand((unsigned int)time(NULL));
    for (auto& tiles : m_Tiles)
    {
        int ranX, ranY;
        ranX = std::rand() % 270 * 2;
        ranY = std::rand() % 100 + tileCount * 110;
        tiles->init(ranX, ranY);

        tX[tileCount] = ranX;
        tY[tileCount] = ranY;

        tileCount++;
    }

}

void TileSpawner::draw() {
    for (auto& tiles : m_Tiles)
    {
        tiles->draw();
    }
}

void TileSpawner::update() {
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

bool TileSpawner::platformCheck(int i) {
    pX = m_player->getXpos();
    pY = m_player->getYpos();
    pW = m_player->getWidth() - 10;
    pH = m_player->getHeight() - 15;
    tW = m_Tiles[i]->getWidth();
    tH = m_Tiles[i]->getHeight();

    if (pX + pW > tX[i] && pX < tX[i] + tW) {
        if (pY + pH <= tY[i] + 30 && pY + pH > tY[i]) {
            if (m_player->jumpHeight >= 0) {
                std::cout << pX << " , " << pY << " : " << tX[i] << " , " << tY[i] << std::endl;
                touchPlatform = true;
                return true;
            }
        }
    }
    return false;
}

TileSpawner* TileSpawner::s_pInstance = 0;