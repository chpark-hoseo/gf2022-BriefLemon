#include "Tile.h"
#include "InputHandler.h"
#include <cstdlib>
#include <ctime>

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

void Tile::init(int ranX, int ranY) {
    m_position.setX(ranX);
    m_position.setY(ranY);
}

void Tile::draw()
{
    SDLGameObject::draw();
}

void Tile::update()
{
    
}

void Tile::clean() {}