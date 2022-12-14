
#include <string>

#include "raylib.h"
#include "raymath.h"

#include "Character.h"
#include "Enemy.h"
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

  // Player
  Character knight(windowWidth, windowHeight);

  std::string idle[]{
      "./characters/goblin_idle_spritesheet.png",
      "./characters/slime_idle_spritesheet.png"};
  std::string run[]{
      "./characters/goblin_run_spritesheet.png",
      "./characters/slime_run_spritesheet.png"};
  const int sizeOfEnemies = 6;
  Enemy *enemies[sizeOfEnemies];

  for (int index = 0; index < sizeOfEnemies; index++)
  {
    enemies[index] = new Enemy(Vector2{static_cast<float>(index * 1000), static_cast<float>(index * 500)},
                               LoadTexture(idle[index % 2].c_str()),
                               LoadTexture(run[index % 2].c_str()));

    enemies[index]->setTarget(&knight);
  }

  // Props
  Prop props[]{
      Prop{Vector2{600.f, 300.f}, LoadTexture("./nature_tileset/Rock.png")},
      Prop{Vector2{400.f, 500.f}, LoadTexture("./nature_tileset/Log.png")}};

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

    // draw props
    // auto tells the complier to find out the type
    for (auto prop : props)
    {
      prop.Render(knight.getWorldPos());
    }

    // checks if the knight is alive
    if (knight.getAlive())
    {
      // show health
      std::string knightsHealth = "Health: ";

      knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);

      DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
    }
    // checks if the knight is dead
    else
    {
      DrawText("Game Over!", 55.f, 45.f, 40, RED);

      EndDrawing();
      continue;
    }

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

    for (auto prop : props)
    {
      if (CheckCollisionRecs(
              prop.getCollisionRec(knight.getWorldPos()),
              knight.getCollisionRec()))
      {
        knight.undoMovement();
      }
    }

    for (auto enemy : enemies)
    {
      enemy->tick(GetFrameTime());

      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
        if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
        {
          enemy->setAlive(false);
        }
      }
    }

    // End Game Logic

    EndDrawing();
  }

  UnloadTexture(map);

  CloseWindow();
}
