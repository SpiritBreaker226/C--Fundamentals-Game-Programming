#include "raylib.h"

int main()
{
  // window dimensions
  const int windowWidth{1024};
  const int windowHeight{450};

  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

  // acceleration due to gravity (pixels/frame)/frame
  const int gravity{1};

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

    // perform ground check
    if (posY >= (windowHeight - height))
    {
      // rectangle the ground
      velocity = 0;
    }
    else
    {
      // rectangle in the air
      velocity += gravity;
    }

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
