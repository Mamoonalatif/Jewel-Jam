# Jewel Jam

Jewel Jam is a captivating match-3 2D puzzle game developed in C++ using the OpenGL Utility Toolkit (GLUT). The game challenges players to swap and match adjacent gems to create lines of three or more of the same type, earning points and progressing through increasingly challenging levels.

## Table of Contents

- [Features](#features)
- [Gameplay Overview](#gameplay-overview)
- [Game Architecture](#game-architecture)
- [Code Structure](#code-structure)
- [How to Build and Run](#how-to-build-and-run)
- [Controls](#controls)
- [Saving Progress and Highscores](#saving-progress-and-highscores)
- [Screenshots](#screenshots)
- [Contributing](#contributing)
- [License](#license)

---

## Features

- **Classic Match-3 Gameplay:** Swap adjacent gems to line up three or more and score points.
- **Multiple Gem Types:** Includes various shapes such as circles, squares, triangles, diamonds, and pentagons.
- **Graphical User Interface:** Built with C++ and GLUT for smooth 2D rendering and mouse/keyboard interaction.
- **Score and Progress Tracking:** Highscore system that saves and loads player progress.
- **Menu System:** Main menu, pause, instructions, and score view are implemented for a complete game experience.
- **Responsive Controls:** Supports intuitive mouse interaction for gem swapping and menu navigation.
- **Persistent Storage:** Player scores and progress are saved to files and loaded on game start.

---

## Gameplay Overview

- The player is presented with an 8x8 grid (board) filled with different gems.
- By clicking and dragging, players can swap adjacent gems.
- Matching three or more gems of the same type in a row or column clears them and increases the player's score.
- New gems fall from the top to fill empty spaces after matches.
- Game ends when no more moves are possible or when a specific game-over condition is met.

---

## Game Architecture

### Main Components

- **GameBoard**: Manages the 2D grid of gems, renders the board, handles user input, and executes the core game logic for matching and swapping gems.
- **Gems and Gem Types**: Base class `Gems` with derived classes for each shape (e.g., `Triangle`, `Circle`, `Diamond`, `Pentagon`, `Square`), each representing a different gem type on the board.
- **Player**: Stores player name and current score.
- **Highscore**: Handles saving, loading, and updating high scores to files.
- **Menu**: Renders the main menu, pause menu, instructions, and score screens.
- **GameManager**: Controls the game state (main menu, play, pause, end, instructions, score screen), and routes input/events accordingly.

### Core Flow

- The game initializes OpenGL and GLUT, sets up the window, and enters the main loop.
- Input handlers manage keyboard and mouse events for gameplay and menu navigation.
- The `GameBoard` manages gem swapping and matching logic, updates the board, and triggers screen redraws.
- High scores and player progress are saved to and loaded from text files.

---

## Code Structure

- `Source.cpp`: Main source file. Contains the primary logic for game loop, input handling, and class implementations.
- `GameBoard.h` / `GameBoard.cpp`: Implementation of the game board and gem management.
- `GameManager.h` / `GameManager.cpp`: Manages overall game states and transitions.
- `Highscore.h` / `Highscore.cpp`: Highscore management, saving/loading from files.
- `Menu.h`: Menu system and rendering options.
- `Player.h`: Player data management.
- `Jewel Jam.cpp`: Alternative main file focusing on OpenGL setup and board interaction.

### Key Classes and Their Responsibilities

- **GameBoard**: Handles 2D array of gems, matching logic, rendering, and input.
- **Gems**: Abstract class with derived types for each gem shape.
- **Player**: Stores player name and score.
- **Highscore**: Updates and persists high score and progress.
- **Menu**: Draws main menu and sub-menus.
- **GameManager**: Routes game state (play, pause, menu, instructions, score).

---

## How to Build and Run

### Prerequisites

- C++ compiler (supporting C++11 or later)
- [OpenGL](https://www.opengl.org/) development libraries
- [GLUT](https://www.opengl.org/resources/libraries/glut/) (or FreeGLUT) installed

### Build Instructions (Example for Linux/Windows)

```sh
# Linux (assuming FreeGLUT is installed)
g++ Source.cpp GameManager.cpp Highscore.cpp -o JewelJam -lGL -lGLU -lglut

# Windows (using MinGW and FreeGLUT)
g++ Source.cpp GameManager.cpp Highscore.cpp -o JewelJam.exe -lfreeglut -lopengl32 -lglu32
```

Then run the executable:

```sh
./JewelJam
# or on Windows
JewelJam.exe
```

---

## Controls

- **Mouse**
  - Click and drag to swap adjacent gems.
  - Click menu buttons to navigate.
- **Keyboard**
  - Key bindings can be extended in `keyboard()` function (see `Source.cpp`).

---

## Saving Progress and Highscores

- Highscores are automatically saved to `highscore.txt` in the game directory.
- Player progress (name and score) saved to `playerProgress.txt`.
- The highscore system loads existing scores at startup and updates them as needed.

---

## Screenshots

![Game Board](https://github.com/Mamoonalatif/Jewel-Jam/assets/151760913/e82753a2-afc0-4df3-a44c-8729dbc21e70)
![Menu](https://github.com/Mamoonalatif/Jewel-Jam/assets/151760913/722f260e-f612-42a2-83c3-365d7c237816)

---

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request. For major changes, open an issue first to discuss your ideas.

