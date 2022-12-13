#include "raylib.h"
#include "raymath.h"

#include "Character.h"
#include "Prop.h"

int main()
{
  // window dimensions
  const int windowWidth{384};
  const int windowHeight{384};

  InitWindow(windowWidth, windowHeight, "Classy Clash!");

  // Map
  Texture2D map = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");
  Vector2 mapPos{0.0, 0.0};
  const float mapScale{4.f};

  Character knight(windowWidth, windowHeight);

  // Props
  Prop rock{Vector2{}, LoadTexture("./nature_tileset/Rock.png")};

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
    DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

    // objects
    rock.Render(knight.getWorldPos());

    // Characters
    knight.tick(GetFrameTime());

    // Check map bounds
    if (knight.getWorldPos().x < 0.f ||
        knight.getWorldPos().y < 0.f ||
        knight.getWorldPos().x + windowWidth > map.width * mapScale ||
        knight.getWorldPos().y + windowHeight > map.height * mapScale)
    {
      knight.undoMovement();
    }

    // End Game Logic

    EndDrawing();
  }

  UnloadTexture(map);

  CloseWindow();
}
