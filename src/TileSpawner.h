#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Tile.h"
#include <vector>

class TileSpawner{
public:

    static TileSpawner* Instance()
    {
        if (s_pInstance == 0)
            s_pInstance = new TileSpawner();
        return s_pInstance;
    }

	std::vector<Tile*> m_Tiles;

    void init();
    void draw();
    void update();

    void setGameObject(Player* player);

private:
    
    bool platformCheck(int i);

    Player* m_player;

    TileSpawner() {}
    static TileSpawner* s_pInstance;

    int tileCount = 0;
    int pX, pY, pW, pH;
    int tX[20], tY[20], tW, tH;

    bool touchPlatform = false;
};