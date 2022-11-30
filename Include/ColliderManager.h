#pragma once
#include "Player.h"
#include "Tile.h"

class ColliderManager {
public:
	static ColliderManager* instance()
	{
		if (s_pInstance == NULL)
			s_pInstance = new ColliderManager;
		return s_pInstance;
	}

	void setGameObject(Player* player, Tile* tile);
	void update();

private:
	ColliderManager() = default;
	static ColliderManager* s_pInstance;

	Player* m_player;
	Tile* m_tile;

	int pX, pY;
	int tX, tY;

}typedef TheCollider;