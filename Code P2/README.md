# Alien vs. Zombie

Alien vs Zombie is a turn-based combat game in which the player controls Alien to defeat a group of Zombies. Prior to the game, the player can customize settings including game board dimensions and number of zombies. The player can also save a game into a file and load a game from a file.

Please provide the YouTube link to your [Video Demo](https://youtu.be/Z1X3FdBFhjs).

## Compilation Instructions

Provide instructions on how to compile your program, especially when it is non-trivial.

For example:

```
g++ pf\*.cpp main.cpp -DDEMO -o alienVsZombieGame
```

## User Manual

The game has main two user roles, namely the Alien Player and the Zombie Player (from 1 to 9).
In order to play the game, first of all compile it using the above mentioned compilation command.
Then, run the complied game from the CLI.
After that the game will ask you to provide few basic settings to start the game, which are:

- Row Count - The number of rows, you want for your game board.
- Column Count - The number of columns, you want for your game board.
- Zombie Count - The number of zombies, you want for your game board.

After that game board will be automatically rendered and you can play it using the following commands:

- **up** - Alien to move up.
- **down** - Alien to move down.
- **left** - Alien to move left.
- **right** - Alien to move right.
- **arrow** - Switch the direction of an arrow object in the game board. (The player will be asked to enter the row and column of the arrow object to switch, followed by the direction of the arrow object to switch to.)
- **help** - List and describe the commands that the player can use in the game.
- **save** - Save the current game to a file.
- **load** - Load a saved game from a file.
- **quit** - Quit the game while still in play.

## Progress Log

- [Part 1](PART1.md)
- 

## Contributors

Please replace the following with your group members' names. 

- MOHAMED MAHMOUD ABDELAZIM ABOUELMAATI  
- SULTAN ABDULLAH SALEM BAHASAN
- ALI AHMED ALI AL SILLAK