#include "raylib.h"
#include "raymath.h"

int main()
{
  // window dimensions
  const int windowWidth{384};
  const int windowHeight{384};

  InitWindow(windowWidth, windowHeight, "Classy Clash!");
  // Map
  Texture2D map = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");
  Vector2 mapPos{0.0, 0.0};
  const float speed = 4.0;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // Start Game Logic

    // direction is the oppose way you want to go
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
      direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
      direction.x += 1.0;
    if (IsKeyDown(KEY_W))
      direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
      direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
      // set map = mapPos - direction (or movement vector)
      mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
    }

    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

    // End Game Logic

    EndDrawing();
  }

  UnloadTexture(map);

  CloseWindow();
}
