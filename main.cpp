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

  const float knightMaxFrames = 6.0f;
  Texture2D knight = LoadTexture("./characters/knight_idle_spritesheet.png");
  Vector2 knightPos{
      (float)windowWidth / 2.0f - 4.0f * (0.5f * (float)knight.width / knightMaxFrames),
      (float)windowHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)};

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

    // draw the map
    DrawTextureEx(map, mapPos, 0.0, 4.0f, WHITE);

    // draw the character
    Rectangle knightSourceRec{
        0.f,
        0.f,
        (float)knight.width / knightMaxFrames,
        (float)knight.height};
    Rectangle knightDestRec{
        knightPos.x,
        knightPos.y,
        4.f * (float)knight.width / knightMaxFrames,
        4.f * (float)knight.height};

    DrawTexturePro(knight, knightSourceRec, knightDestRec, Vector2{}, 0.f, WHITE);

    // End Game Logic

    EndDrawing();
  }

  UnloadTexture(map);
  UnloadTexture(knight);

  CloseWindow();
}
