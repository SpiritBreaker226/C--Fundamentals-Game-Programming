#include "raylib.h"

int main()
{
  // window dimensions
  int width{800};
  int height{450};

  // create a window
  InitWindow(width, height, "Jason Stathopulos");

  // circle coordinates
  int circle_x{200};
  int circle_y{200};

  // axe coordinates
  int axe_x{400};
  int axe_y{0};

  // sets the target Frames per second (FPS)
  SetTargetFPS(60);
  while (WindowShouldClose() == false)
  {
    // init the drawing to the window
    BeginDrawing();

    // clears the background to prevent flickering,
    // and want to avoid causing sizes.
    ClearBackground(WHITE);

    // Game Logic Begins

    DrawCircle(circle_x, circle_y, 25, BLUE);
    DrawRectangle(axe_x, axe_y, 50, 50, RED);

    // add boundary on the right side
    if (IsKeyDown(KEY_D) && circle_x < width)
    {
      circle_x = circle_x + 10;
    }

    // add boundary on the left side
    if (IsKeyDown(KEY_A) && circle_x > 0)
    {
      circle_x = circle_x - 10;
    }

    // Game Logic Ends

    // teardown the window
    EndDrawing();
  }
}
