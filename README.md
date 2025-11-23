# SpellPop — Dual-Mode Word Gauntlet

SpellPop is a C++ educational game suite featuring multiple word-based game modes designed to test typing speed, vocabulary, and programming knowledge.

## Game Modes

### 1. SpellPop 3D
A real-time bubble-typing challenge. Words float in bubbles; type them correctly before they pop or float away!

### 2. Hangman (C++ Edition)
A classic hangman game with a twist.
- **Progression System**: You must achieve a score of **95% or higher** to advance to the next level.
- **Educational Content**: Features vocabulary from *C++ Programming: From Problem Analysis to Program Design (8th Edition)* by D.S. Malik.
- **Levels**: Starts at Chapter 1 and progresses through the book.

### 3. CrossFill
A crossword-style puzzle engine.
- **Standard Mode**: General knowledge topics (Astronomy, Biology, etc.).
- **C++ Mode**: Procedurally generated crosswords using C++ terminology from Chapter 1.
- **Features**:
    - Auto-advancing cursor.
    - Smart direction switching (arrow keys & mouse click).
    - Active word highlighting.

## Controls

### General
- **Esc**: Return to Main Menu

### SpellPop 3D
- **Typing**: Type the words visible on screen.
- **Enter/Space**: Submit word.
- **Backspace**: Correct typos.

### CrossFill
- **Arrow Keys**: Move cursor.
- **Typing**: Fill in letters.
- **Click**: Select cell (Click again to toggle Across/Down).
- **Tab**: Toggle direction.
- **Backspace**: Clear cell.

## Build Instructions

### Prerequisites
- **CMake** (3.10 or higher)
- **C++ Compiler** (supporting C++17)
- **Visual Studio** (recommended for Windows)

### Building
1. Clone the repository:
   ```bash
   git clone https://github.com/TaoAthe/SpellPop.git
   cd SpellPop
   ```
2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```
3. Configure with CMake:
   ```bash
   cmake ..
   ```
4. Build:
   ```bash
   cmake --build . --config Debug
   ```
5. Run:
   ```bash
   .\Debug\SpellPop.exe
   ```

## Dependencies
- **SFML 2.6.1**: Automatically fetched via CMake (FetchContent).

## License
This project is for educational purposes.
