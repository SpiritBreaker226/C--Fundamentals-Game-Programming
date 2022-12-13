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

  const int maxFrames{6};
  Texture2D knight = LoadTexture("./characters/knight_idle_spritesheet.png");
  Vector2 knightPos{
      (float)windowWidth / 2.0f - 4.0f * (0.5f * (float)knight.width / maxFrames),
      (float)windowHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)};

  // 1:  facing right, -1: facing left
  float rightLeft{1.f};
  // animation variables
  float runningTime{};
  float updateTime{1.f / 12.f};
  float frame{};

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    const float dT{GetFrameTime()};

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

      rightLeft = direction.x < 0.f ? -1.f : 1.f;
    }

    // draw the map
    DrawTextureEx(map, mapPos, 0.0, 4.0f, WHITE);

    // update animation frame
    runningTime += dT;

    if (runningTime > updateTime)
    {
      runningTime = 0.f;

      frame++;

      if (frame > maxFrames)
      {
        frame = 0;
      }
    }

    // draw the character
    Rectangle knightSourceRec{
        frame * (float)knight.width / maxFrames,
        0.f,
        // flips the sprite by changing the value from positive to negative and back again
        rightLeft * (float)knight.width / maxFrames,
        (float)knight.height};

    Rectangle knightDestRec{
        knightPos.x,
        knightPos.y,
        4.f * (float)knight.width / maxFrames,
        4.f * (float)knight.height};

    DrawTexturePro(knight, knightSourceRec, knightDestRec, Vector2{}, 0.f, WHITE);

    // End Game Logic

    EndDrawing();
  }

  UnloadTexture(map);
  UnloadTexture(knight);

  CloseWindow();
}
