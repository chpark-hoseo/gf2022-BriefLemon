#include "ColliderManager.h"
#include <iostream>

void ColliderManager::setGameObject(Player* player, Tile* tile){
	this->m_player = player;
	this->m_tile = tile;
	m_Tiles.push_back(tile);
}

void ColliderManager::update(std::vector<Tile*> m_Tiles) {

	for (int i = 0; i < m_Tiles.size(); i++)
	{
		if (isOnPlatform) {
			m_player->platformCheck(tY[i]);
			if (pX + pW < tX[i] || pX > tX[i] + tW[i] || m_player->isJump) {
				isOnPlatform = false;
				m_player->onFloor = false;
			}
		}

		pX = m_player->getXpos();
		pY = m_player->getYpos();
		pW = m_player->getWidth();
		pH = m_player->getHeight();
		tX[i] = m_Tiles[i]->getXpos();
		tY[i] = m_Tiles[i]->getYpos();
		tW[i] = m_Tiles[i]->getWidth();
		tH[i] = m_Tiles[i]->getHeight();

		if (pX + pW > tX[i] && pX < tX[i] + tW[i]) {
			if (pY + pH <= tY[i] + 50 && pY + pH > tY[i] - 20) {
				if (m_player->jumpHeight > 0) {
					std::cout << pX << " , " << pY << " : " << tX[i] << " , " << tY[i] << std::endl;
					isOnPlatform = true;
				}
			}
		}
	}
}

void ColliderManager::checkPlatform() {
	//if (isOnPlatform) {
	//	m_player->platformCheck(tY);
	//	if (pX + pW < tX || pX > tX + tW || m_player->isJump) {
	//		isOnPlatform = false;
	//		m_player->onFloor = false;
	//	}
	//}
}