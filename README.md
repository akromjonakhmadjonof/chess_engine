# User Manual – Chess Engine (White Player)

## 1. Overview
This application is a simple chess engine developed in C++. It provides a graphical chessboard interface where the user plays as **White**, and the computer (AI) plays as **Black**.

The engine uses classical artificial intelligence techniques, including the minimax algorithm and alpha-beta pruning, to determine its moves. The system is designed for educational purposes and demonstrates how a basic chess engine operates.

---

## 2. System Requirements
- A computer capable of running C++ applications
- Built using CMake (compatible with CLion or similar IDEs)
- Graphics support for rendering the chessboard window

---

## 3. Launching the Application
1. Open the project in your IDE (e.g., CLion).
2. Build the project using CMake.
3. Run the executable (`main.cpp`).

Once launched, a window will appear displaying the chessboard.

---

## 4. Game Interface
- White pieces are positioned at the bottom
- Black pieces are positioned at the top
- The title bar indicates the current turn (e.g., "White to move")
- Pieces are displayed using graphical icons

---

## 5. Controls and Gameplay

### 5.1 Playing as White
- The user always plays as White
- White moves first

### 5.2 Making a Move
1. Select a white piece
2. Select a valid destination square
3. The move will be executed if it follows chess rules

### 5.3 Computer Moves
- After your move, the AI automatically plays as Black
- The AI uses minimax and alpha-beta pruning

---

## 6. Game Rules
- Standard piece movements are enforced
- Illegal moves are not allowed
- Captures are handled automatically

---

## 7. Game Flow
1. Game starts from the standard chess position
2. Player (White) makes a move
3. AI (Black) responds
4. Repeat until the game ends

---

## 8. Game End Conditions
- Checkmate
- Stalemate
- Manual termination (if applicable)

---

## 9. Limitations
The engine implements core chess rules but does not include some advanced rules. In particular:

- En passant is not implemented
- Castling may be limited or not supported
- Pawn promotion may default to a queen without user choice

As a result, some situations may differ from official chess rules.

---

## 10. Tips
- The AI uses a simple material-based evaluation
- It may miss long-term strategies
- Use this program as a learning tool

---

## 11. Summary
This chess engine allows users to play as White against a basic AI opponent. It demonstrates core AI concepts in a simple and understandable way.

## Chess Engine Paper
https://docs.google.com/document/d/1IaiYV6u4O2_QWNLBb14aCFSdq01wVrZQd3WghO9Onl4

