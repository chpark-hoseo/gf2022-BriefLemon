#include "ColliderManager.h"
#include <iostream>

void TheCollider::setGameObject(Player* player, Tile* tile){
	this->m_player = player;
	this->m_tile = tile;
}

void TheCollider::update() {
	pX = m_player->getXpos();
	pY = m_player->getYpos();
	tX = m_tile->getXpos();
	tY = m_tile->getYpos();
	std::cout << pX << " , " << pY << " : " << tX << " , " << tY << std::endl;
}

TheCollider* TheCollider::s_pInstance = NULL;