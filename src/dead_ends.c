#include "dead_ends.h"

void remove_dead_ends(Grid* grid) {
  bool done = false;

	while (!done)
	{
		done = true;
		for (int y = 1; y < grid->height - 1; ++y) {
			for (int x = 1; x < grid->width - 1; ++x) {
				Position *tile = &grid->data[y][x];
				if (tile->tile != WALL) {
					int passages = 0;
					for (int i = 0; i < NUM_DIRECTIONS; ++i) {
						int dx, dy;
						directionToDelta(CARDINAL[i], &dx, &dy);
						if (grid->data[y + dy][x + dx].tile != WALL) {
							++passages;
						}
					}
					if (passages == 1) {
						done = false;
						tile->tile = WALL;
						tile->region = -1;
					}
				}
			}
		}
	}
}
