#include "Tile.h"
#include "InputHandler.h"

Tile::Tile(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Tile::draw()
{
    SDLGameObject::draw();
}

void Tile::update()
{
    handleInput();
    SDLGameObject::update();
}

void Tile::clean() {}