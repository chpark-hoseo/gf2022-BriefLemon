#pragma once
#include "Vector2D.h"
#include "Player.h"

enum Tile {
	TILE_EMPTY = ' ',
	TILE_ZERO = '\0',
	TILE_FULL = '#'
};

const int TILEMAP_SIZE_X = 20;
const int TILEMAP_SIZE_Y = 24;

const int TILE_SIZE = 64;

// What happens when we get out of grid horizontally
#define OUTSIDE_TILE_HORIZONTAL TILE_FULL
// What happens when we get out of grid vertically
#define OUTSIDE_TILE_VERTICAL TILE_EMPTY

#define arrayNumItems(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef uint8_t Tilemap[TILEMAP_SIZE_Y][TILEMAP_SIZE_X + 1];

const Tilemap screenTilemaps[] = {
    {
        // Index zero is empty
        // This index is reserved for 'invalid tilemap'
    },
    {
        "#  ########    #",
        "# ##      ##   #",
        "# # #####  ### #",
        "# # #   #  # # #",
        "# # #####  # # #",
        "# #        # # #",
        "# #      ### # #",
        "# #        ### #",
        "# ###      #   #",
        "# #        #   #",
        "# ##       #   #",
        "####   #########",
    },
    {
        "####      ######",
        "###        #####",
        "###  ###    ####",
        "###  ##     ####",
        "###       ######",
        "###    #########",
        "###  #    ######",
        "###        #####",
        "###         ####",
        "##  ##      ####",
        "##        ######",
        "##        ######",
    },
    // Starting screen:
    {
        "##        ######",
        "######       ###",
        "######        ##",
        "######     #####",
        "##       #######",
        "#              #",
        "#  #######   # #",
        "#  ##    #   # #",
        "#     ##     ###",
        "###      # #####",
        "#### #     #####",
        "################",
    },
};

class Map {
private:
    Player* m_player;

public:
	void drawMap();
	Tile tilemapGetTile(const Tilemap* tilemap, int x, int y);
	Tile tilemapGetTileFullOutside(const Tilemap* tilemap, int x, int y);
	Vector2D worldToScreen(const Vector2D worldSpacePos);
	bool tilemapIsTileFull(const Tilemap* tilemap, int x, int y);
};