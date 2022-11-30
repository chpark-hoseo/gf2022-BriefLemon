#include "Tile.h"
#include "InputHandler.h"

Tile::Tile(const LoaderParams* pParams) : SDLGameObject(pParams) {}

int Tile::getXpos() {
    return m_position.getX();
}
int Tile::getYpos() {
    return m_position.getY();
}
int Tile::getWidth() {
    return m_width;
}
int Tile::getHeight() {
    return m_height;
}

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