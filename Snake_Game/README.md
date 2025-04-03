# Snake Game

A classic terminal-based Snake game implemented in C using the ncurses library.

## Description

This is a feature-complete implementation of the classic Snake game that runs in your terminal. The game includes:

- Smooth snake movement with arrow key controls
- Score tracking
- Randomly generated food
- Game over detection for wall and self collisions
- Color-coded display elements
- Clean, modular code structure

## Requirements

- C compiler (gcc recommended)
- ncurses library
- make (for building)

## Installation

### Dependencies

On Debian/Ubuntu:
```bash
sudo apt-get install gcc make libncurses5-dev
```

On macOS:
```bash
brew install gcc make ncurses
```

### Building

To build the game:

```bash
cd Snake_Game
make
```

## Usage

Launch the game with:

```bash
./snake_game
```

### Controls

- Arrow keys: Move the snake
- Space: Restart the game after Game Over
- ESC: Quit the game

## Project Structure

```
snake_game/
├── include/             # Header files
│   ├── snake.h          # Main header with core declarations
│   ├── init.h           # Header for initialization functions
│   ├── input.h          # Header for input handling
│   ├── collision.h      # Header for collision detection
│   ├── render.h         # Header for rendering functions
│   └── game_logic.h     # Header for game logic functions
├── src/                 # Source files
│   ├── main.c           # Main game loop
│   ├── init.c           # Implementation of initialization functions
│   ├── input.c          # Implementation of input handling
│   ├── collision.c      # Implementation of collision detection
│   ├── render.c         # Implementation of rendering functions
│   └── game_logic.c     # Implementation of game logic functions
├── obj/                 # Object files (created during build)
├── Makefile             # Build system
└── README.md            # This file
```

## Code Organization

The code is organized following a modular design pattern:

- **main.c**: Contains the main game loop and program entry point
- **init**: Game initialization and cleanup functions
- **input**: Keyboard input handling
- **collision**: Collision detection logic
- **render**: Drawing functions for game elements
- **game_logic**: Core game mechanics and state updates

## Customization

You can customize the game by modifying the following constants in `include/snake.h`:

- `MAX_SCORE`: Maximum achievable score
- `FRAME_TIME`: Speed of the game (microseconds between frames)

Screen size can be modified in `src/init.c` by changing the `sw` and `sh` values.

## Future Improvements

- [ ] Add difficulty levels
- [ ] Implement high score tracking
- [ ] Add sound effects
- [ ] Create a main menu
- [ ] Add obstacles or special food items

## Contributing

1. Fork the project
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request


## Acknowledgments

- Inspired by the classic Snake game
- Built with ncurses, a powerful terminal manipulation library
