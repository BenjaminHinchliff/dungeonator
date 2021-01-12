# Dungeonator

## About

This is a small C library designed for people who just want procedural rouguelike dungeon generation,
and don't want to have to go through the trouble of doing it themselves. It's written in pure C99 to allow it
to be bound to basically every language that exists, if one so chooses.

The algorithm used is a variant of the one described [here](https://journal.stuffwithstuff.com/2014/12/21/rooms-and-mazes/).

## Usage Example

```c
#include "dungeonator.h"

int main() {
	// the random generator must be seeded or a crash will occur
	seedDungeonatorRNG();
	// the output grid for dungeonator
	Grid grid;
	// make sure to check if it was successful (out of memory, etc)
	bool success = generateDungeon(&grid, 51, 27, 1000, 2);
	if (!success) {
		fprintf(stderr, "failed to generate dungeon");
		return 1;
	}
	// debug print the grid (as an example)
	printGrid(&grid);

	// prevent memory leak
	freeGrid(&grid);
	return 0;
}
```

you can find the full docs for generateDungeon [here](https://benjaminhinchliff.github.io/dungeonator/generate_8h.html#aab5f8e2efd492a284e90f05f51461309)

## API Docs

The full documentation for the API can be found hosted on github pages https://benjaminhinchliff.github.io/dungeonator/

## Building

If you're integrating into another cmake project, just add this using add_subdirectory, and everything else will be handled automatically. Building tests and docs will be off by default (you can turn them on with cmake options if you so choose)

Building it on it's own it should be just as easy - just run cmake and it will handle fetching libraries (if needed) for tests and random number generation. If you want to build the docs, Doxygen must be installed and accessible to cmake. If you're building the tests, CMAKE_UNITY_BUILD will be turned on for non-windows platforms using the Ninja generator due to some bugs with \_\_FILE\_\_ documented [here](https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/TroubleshootingMisconfiguredBuild.html).

## Completion Status:
- [X] room placement
- [X] maze generation (recursive backtracking)
- [X] spanning tree generation (door placement)
- [X] dead-end cleanup
- [X] approval testing
- [X] code cleanup for room placement and generation logic
- [X] fix crashing on malloc errors (I was lazy)
- [X] documentation (using Doxygen)
- [X] complete README
- [X] bundled alternative to `rand()` so tests are less brittle
- [X] wasm demo
- [ ] rust bindings
