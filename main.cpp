#include "raylib.h"

int main()
{
  // window dimensions
  const int windowWidth{1024};
  const int windowHeight{450};

  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

  // rectangle dimensions
  const int width{50};
  const int height{80};

  // places the rectangle on the ground
  int posY{windowHeight - height};
  int velocity{0};

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();

    ClearBackground(WHITE);

    // Start Game Logic

    if (IsKeyPressed(KEY_SPACE))
    {
      velocity -= 10;
    }

    posY += velocity;

    DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

    // End Game Logic

    EndDrawing();
  }

  // CLoses the window properly
  CloseWindow();
}
