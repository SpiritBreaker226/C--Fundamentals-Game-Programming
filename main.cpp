#include "raylib.h"

int main()
{
  int width = 350;

  // create a window
  InitWindow(width, 900, "Jason Stathopulos");

  while (true)
  {
    // init the drawing to the window
    BeginDrawing();

    // clears the background to prevent flickering,
    // and want to avoid causing sizes.
    ClearBackground(RED);

    // treadown the window
    EndDrawing();
  }
}
