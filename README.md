# ChessPlusPlus

A simple chess game including it's own chess engine and AI.

[Latest release](https://github.com/Saduras/ChessPlusPlus/releases/tag/v1.2)

## Features
- Simple window view with drag'n'drop interaction
- Move generation
- Move validation
- Agents:
  - Human player
  - Random move AI
  - MiniMax AI with alpha-beta-pruning
- Unit test suit for the chess engine

## Multi-threading

The MiniMax agent runs on a separate thread to avoid blocking the window refreshing while computing new moves. 

I implemented a version that schedules search on multiple sub-trees asynchronously. However, doing this the naive way is not compatible with alpha-beta-pruning. While pruning works fine within a sub-tree, breaking it for the highest search level is costly enough to make the async search just as slow as the single-threaded search. It computes faster but requires more search steps. More research for an algorithm that is suited for parallelization is required. 

## Develop environment
- Windows 10
- Visual Studio 2017

## Dependencies
- [SFML](https://www.sfml-dev.org/)
