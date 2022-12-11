#pragma once
#include "Player.h"
#include <vector>

class ScreenManager {
private:
    ScreenManager() {}
    static ScreenManager* s_pInstance;

    SDL_Renderer* m_pRenderer;
    Player* m_player;
    std::vector<GameObject*> m_buttons;

    bool isClear = false;

public:
    static ScreenManager* Instance()
    {
        if (s_pInstance == 0)
            s_pInstance = new ScreenManager();
        return s_pInstance;
    }

    void init(Player* player, SDL_Renderer* renderer);
    void draw();
    void update();
    void clean();

};

typedef ScreenManager TheScreenManager;