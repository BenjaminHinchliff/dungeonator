# Dungeonator

> :warning: this project isn't totally ready at this point, but the bones are there

## About

This is a small C library designed for people who just want procedural rouguelike dungeon generation,
and don't want to have to go through the trouble of doing it themselves. It's written in pure ANSI C to allow it
to be bound to basically every language that exists, if one so chooses.

## Completion Status:
- [X] room placement
- [X] maze generation (recursive backtracking)
- [X] spanning tree generation (door placement)
- [ ] dead-end cleanup
- [X] approval testing
- [ ] code cleanup for room placement and generation logic
- [ ] fix crashing on malloc errors (I was lazy)
- [ ] documentation (using Doxygen)
- [ ] complete README
- [ ] bundled alternative to `rand()` so tests are less brittle
- [ ] rust bindings
