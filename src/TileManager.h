#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Tile.h"
#include <vector>

class TileManager{
public:

    static TileManager* Instance()
    {
        if (s_pInstance == 0)
            s_pInstance = new TileManager();
        return s_pInstance;
    }

    void init(int i);
    void draw();
    void update();
    void clean();

    void setGameObject(Player* player);

private:
    TileManager() {}
    static TileManager* s_pInstance;

    std::vector<Tile*> m_Tiles;
    Player* m_player;

    int tileCount = 0;
    int ranX, ranY;
    int pX, pY, pW, pH;
    int tX[20], tY[20], tW, tH;

    bool touchPlatform = false;

    bool platformCheck(int i);
};