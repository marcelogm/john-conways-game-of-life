# Conway's Game of Life Implementation

A simple implementation of Conway's Game of Life using C.

## Description

This program simulates Conway's Game of Life, a cellular automaton devised by the mathematician John Conway. The game is played on a grid of cells, each of which can be in one of two states: alive or dead. The state of each cell evolves over time based on a set of rules, giving rise to captivating patterns and behaviors.

For more information, visit [conwaylife.com](https://conwaylife.com/).

## Running

To run this program on your local machine, follow these steps:

1. Clone this repository to your local machine.

2. Compile the program using the following command:

    ```bash
    gcc -o game_of_life game.c -lncurses
    ```

3. Run the compiled program:

    ```bash
    ./game_of_life
    ```

## Usage

Upon launching the program using the compiled executable, the simulation will start with a randomly initialized state of cells. Additional functionalities include:

- Press the `SPACE` key to randomize the grid with a new configuration.
- Press the `ESC` key to exit the simulation.
