#include "raylib.h"

int main()
{
  // window dimensions
  int width{350};
  int height{200};

  // create a window
  InitWindow(width, height, "Jason Stathopulos");

  // circle coordinates
  int circle_x{width / 2};
  int circle_y{height / 2};

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
