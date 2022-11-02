#pragma once
#include "GameObject.h"

class Monster : public GameObject
{
public:
    void load(int x, int y, int width, int height, std::string textureID);
    void draw(SDL_Renderer* pRenderer);
    void update(int spd);
    void clean() {};
private:
    bool isRight = true;
};