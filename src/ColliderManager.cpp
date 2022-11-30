#include "ColliderManager.h"
#include <iostream>

void TheCollider::setGameObject(Player* player, Tile* tile){
	this->m_player = player;
	this->m_tile = tile;
}

void TheCollider::update() {
	pX = m_player->getXpos();
	pY = m_player->getYpos();
	pW = m_player->getWidth();
	pH = m_player->getHeight();
	tX = m_tile->getXpos();
	tY = m_tile->getYpos();
	tW = m_tile->getWidth();
	tH = m_tile->getHeight();

	if (pX > tX - pW && pX < tX + tW) {
		if (pY + pH > tY && pY + pH < tY + tH) {
			std::cout << pX << " , " << pY << " : " << tX << " , " << tY << std::endl;
			m_player->platformCheck(tY);
		}
	}
}

TheCollider* TheCollider::s_pInstance = NULL;