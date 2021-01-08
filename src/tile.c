#include "tile.h"

char getCharacterForTile(Tile tile) {
	switch (tile)
	{
	case WALL:
		return '#';
	case FLOOR:
		return '.';
	case DOOR:
		return '+';
	default:
		fprintf(stderr, "failed to find tile");
		return ' ';
	}
}
