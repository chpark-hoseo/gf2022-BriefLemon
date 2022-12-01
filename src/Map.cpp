#include <SDL2/SDL.h>
#include "Map.h"

void Map::drawMap() {
	int screenIndex = arrayNumItems(screenTilemaps) - getScreenHeightIndex(m_player->getYpos()) - 2;
	if (screenIndex < 0 || screenIndex > arrayNumItems(screenTilemaps)) screenIndex = 0;

	const Tilemap* tilemap = &screenTilemaps[screenIndex % arrayNumItems(screenTilemaps)];

	for (int x = 0; x < TILEMAP_SIZE_X; x++) {
		for (int y = 0; y < TILEMAP_SIZE_Y; y++) {
			if (!tilemapIsTileFull(tilemap, x, y)) continue;

			const Tile tile = tilemapGetTileFullOutside(tilemap, x, y);

			int spriteX = 0;
			int spriteY = 0;

			switch (tile) {
			case TILE_FULL: {
				spriteX = 1;
				spriteY = 1;
			} break;
			}

			drawSpriteSheetTile(tilemapTexture, spriteX, spriteY, TILE_PIXELS, { (float)x * TILE_PIXELS, (float)y * TILE_PIXELS });
		}
	}
}

Tile Map::tilemapGetTile(const Tilemap* tilemap, int x, int y) {
	if (x < 0 || x >= TILEMAP_SIZE_X) return OUTSIDE_TILE_HORIZONTAL;
	if (y < 0 || y >= TILEMAP_SIZE_Y) return OUTSIDE_TILE_VERTICAL;
	return (Tile)(*tilemap)[y][x];
}

Tile Map::tilemapGetTileFullOutside(const Tilemap* tilemap, int x, int y) {
	if (x < 0 || x >= TILEMAP_SIZE_X) return TILE_FULL;
	if (y < 0 || y >= TILEMAP_SIZE_Y) return TILE_FULL;
	return (Tile)(*tilemap)[y][x];
}

Vector2D Map::worldToScreen(const Vector2D worldSpacePos) {
	Vector2D* vector2;

	return vector2->Vector2DScale(worldSpacePos, TILE_SIZE);
}

bool Map::tilemapIsTileFull(const Tilemap* tilemap, int x, int y) {
	const Tile tile = tilemapGetTile(tilemap, x, y);
	if (tile == TILE_EMPTY || tile == TILE_ZERO) return false;
	return true;
}

int getScreenHeightIndex(float height) {
	return floorf(-height / TILEMAP_SIZE_Y);
}

void Map::drawSpriteSheetTile(const Texture texture, const int spriteX, const int spriteY, const int spriteSize,
	const Vector2 position, const Vector2 scale = { 1, 1 }) {
	DrawTextureRec(
		texture,
		{ (float)(spriteX * spriteSize), (float)(spriteY * spriteSize), (float)spriteSize * scale.x, (float)spriteSize * scale.y },
		position, WHITE);
}