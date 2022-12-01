#pragma once
#include "Player.h"
#include "Tile.h"
#include <vector>

class ColliderManager {
public:
	void setGameObject(Player* player, Tile* tile);
	void update(std::vector<Tile*> m_Tiles);

private:

	Player* m_player;
	Tile* m_tile;

	std::vector<Tile*> m_Tiles;

	int pX, pY, pW, pH;
	int tX[20], tY[20], tW[20], tH[20];
	bool isOnPlatform = false;

	void checkPlatform();

};