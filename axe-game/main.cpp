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
  int circle_radius{25};

  // circle edges
  int l_circle_x{circle_x - circle_radius};
  int r_circle_x{circle_x + circle_radius};
  int u_circle_y{circle_y - circle_radius};
  int b_circle_y{circle_y + circle_radius};

  // axe coordinates
  int axe_x{400};
  int axe_y{0};
  int axe_length{50};

  // axe edges
  int l_axe_x{axe_x};
  int r_axe_x{axe_x + axe_length};
  int u_axe_y{axe_y};
  int b_axe_y{axe_y + axe_length};

  int direction{10};

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

    bool collision_with_axe =
        (b_axe_y >= u_circle_y) &&
        (u_axe_y <= b_circle_y) &&
        (l_axe_x <= r_circle_x) &&
        (r_axe_x >= l_circle_x);

    if (collision_with_axe)
    {
      DrawText("Game Over!", 400, 200, 20, RED);
    }
    else
    {
      // update edges
      l_circle_x = circle_x - circle_radius;
      r_circle_x = circle_x + circle_radius;
      u_circle_y = circle_y - circle_radius;
      b_circle_y = circle_y + circle_radius;
      l_axe_x = axe_x;
      r_axe_x = axe_x + axe_length;
      u_axe_y = axe_y;
      b_axe_y = axe_y + axe_length;

      // update collision_with_axe
      collision_with_axe =
          (b_axe_y >= u_circle_y) &&
          (u_axe_y <= b_circle_y) &&
          (l_axe_x <= r_circle_x) &&
          (r_axe_x >= l_circle_x);

      DrawCircle(circle_x, circle_y, circle_radius, BLUE);
      DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

      // move the axe
      axe_y += direction;

      if (axe_y > height || axe_y < 0)
      {
        // reverse the number so
        // plus become minus and minus becomes plus
        direction = -direction;
      }

      // add boundary on the right side
      if (IsKeyDown(KEY_D) && r_circle_x < width)
      {
        circle_x += 10;
      }

      // add boundary on the left side
      if (IsKeyDown(KEY_A) && l_circle_x > 0)
      {
        circle_x -= 10;
      }
    }

    // Game Logic Ends

    // teardown the window
    EndDrawing();
  }
}
