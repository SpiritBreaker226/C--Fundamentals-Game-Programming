#include "raylib.h"
#include "raymath.h"

#include "Character.h"

int main()
{
  // window dimensions
  const int windowWidth{384};
  const int windowHeight{384};

  InitWindow(windowWidth, windowHeight, "Classy Clash!");

  // Map
  Texture2D map = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");
  Vector2 mapPos{0.0, 0.0};

  Character knight;

  knight.setScreenPos(windowWidth, windowHeight);

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // Start Game Logic

    // the world moves in the oppose direction then the user character so that
    // it looks like they are moving but its the world is moving they are standing
    // still.
    mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

    // draw the map
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

    knight.tick(GetFrameTime());

    // End Game Logic

    EndDrawing();
  }

  UnloadTexture(map);

  CloseWindow();
}
