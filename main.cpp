#include "raylib.h"

int main()
{
  // window dimensions
  const int windowWidth{384};
  const int windowHeight{384};

  InitWindow(windowWidth, windowHeight, "Classy Clash!");
  // Map
  Texture2D map = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // Start Game Logic

    Vector2 mapPos{0.0, 0.0};
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

    // End Game Logic

    EndDrawing();
  }

  UnloadTexture(map);

  CloseWindow();
}
