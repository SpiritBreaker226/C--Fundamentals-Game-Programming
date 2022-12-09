#include "raylib.h"

int main()
{
  // window dimensions
  const int windowWidth{1024};
  const int windowHeight{450};

  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

  // acceleration due to gravity (pixels/frame)/frame
  const int gravity{1};

  Texture2D scarfy = LoadTexture("./textures/scarfy.png");
  Rectangle scarfyRec;

  // init scarfyRec
  scarfyRec.width = scarfy.width / 6;
  scarfyRec.height = scarfy.height;
  scarfyRec.x = 0;
  scarfyRec.y = 0;

  Vector2 scarfyPos;
  scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
  scarfyPos.y = windowHeight - scarfyRec.height;

  // checks if the rectangle
  bool isInAir{};

  // jump velocity
  const int jumpVel{-22};

  // places the rectangle on the ground
  int velocity{0};

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();

    ClearBackground(WHITE);

    // Start Game Logic

    // perform ground check
    if (scarfyPos.y >= (windowHeight - scarfyRec.height))
    {
      // no longer in the air
      isInAir = false;

      // rectangle the ground
      velocity = 0;
    }
    else
    {
      // in the air
      isInAir = true;

      // rectangle in the air
      velocity += gravity;
    }

    // jump check
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVel;
    }

    scarfyPos.y += velocity;

    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    // End Game Logic

    EndDrawing();
  }

  UnloadTexture(scarfy);

  // CLoses the window properly
  CloseWindow();
}
