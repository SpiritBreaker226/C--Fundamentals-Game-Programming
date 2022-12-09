#include "raylib.h"

int main()
{
  // window dimensions
  const int windowWidth{1024};
  const int windowHeight{450};

  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();

    ClearBackground(WHITE);

    // Start Game Logic

    // End Game Logic

    EndDrawing();
  }

  // CLoses the window properly
  CloseWindow();
}
