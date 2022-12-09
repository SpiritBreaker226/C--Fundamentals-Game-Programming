#include "raylib.h"

int main()
{
  int width{350};
  int height{900};

  // create a window
  InitWindow(width, height, "Jason Stathopulos");

  while (WindowShouldClose() == false)
  {
    // init the drawing to the window
    BeginDrawing();

    // clears the background to prevent flickering,
    // and want to avoid causing sizes.
    ClearBackground(WHITE);

    DrawCircle(width / 2, height / 2, 25, BLUE);

    // treadown the window
    EndDrawing();
  }
}
