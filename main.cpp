#include "raylib.h"

int main()
{
  // window dimensions
  const int windowWidth{1024};
  const int windowHeight{450};

  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

  // acceleration due to gravity (pixels/frame)/frame
  const int gravity{1'000};

  Texture2D scarfy = LoadTexture("./textures/scarfy.png");
  Rectangle scarfyRec;

  const int scarfyFrames = 6;

  // init scarfyRec
  scarfyRec.width = scarfy.width / scarfyFrames;
  scarfyRec.height = scarfy.height;
  scarfyRec.x = 0;
  scarfyRec.y = 0;

  Vector2 scarfyPos;
  scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
  scarfyPos.y = windowHeight - scarfyRec.height;

  // animation frame
  int frame{};

  // amount of time before we update the animation frame
  const float updateTime{1.0 / 12.0};
  float runningTime{};

  // checks if the rectangle
  bool isInAir{};

  // jump velocity (pixels/second)
  const int jumpVel{-600};

  // places the rectangle on the ground
  int velocity{0};

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    // delta time (time since last frame)
    const float dT{GetFrameTime()};

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
      velocity += gravity * dT;
    }

    // jump check
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVel;
    }

    scarfyPos.y += velocity * dT;

    // update running time
    runningTime += dT;

    if (runningTime >= updateTime)
    {
      runningTime = 0.0;

      // update animation frame
      scarfyRec.x = frame * scarfyRec.width;
      frame++;

      if (frame > scarfyFrames - 1)
      {
        frame = 0;
      }
    }

    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    // End Game Logic

    EndDrawing();
  }

  UnloadTexture(scarfy);

  // CLoses the window properly
  CloseWindow();
}
