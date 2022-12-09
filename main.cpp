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

  while (WindowShouldClose() == false)
  {
    // init the drawing to the window
    BeginDrawing();

    // clears the background to prevent flickering,
    // and want to avoid causing sizes.
    ClearBackground(WHITE);

    // Game Logic Begins

    DrawCircle(circle_x, circle_y, 25, BLUE);

    // Game Logic Ends

    // teardown the window
    EndDrawing();
  }
}
