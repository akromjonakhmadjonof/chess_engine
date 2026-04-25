cmake_minimum_required(VERSION 3.28)
project(chess_engine)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

add_executable(chess_engine
        main.cpp
        src/piece/Piece.cpp
        src/piece/Pawn.cpp
        src/piece/Knight.cpp
        src/ai/ai.cpp
        src/piece/Bishop.cpp
        src/piece/Rook.cpp
        src/piece/Queen.cpp
        src/piece/King.cpp
        src/board/Board.cpp
        src/game/Game.cpp
        src/renderer/Renderer.cpp
)

target_include_directories(chess_engine PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(chess_engine SFML::Graphics SFML::Window SFML::System)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})