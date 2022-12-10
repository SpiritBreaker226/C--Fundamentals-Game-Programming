#include "raylib.h"

int main()
{
  // window dimensions
  const int windowWidth{1024};
  const int windowHeight{450};

  InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

  // acceleration due to gravity (pixels/frame)/frame
  const int gravity{1'000};

  // nebula variables

  const float nebulaFrames = 8.0;

  Texture2D nebula = LoadTexture("./textures/12_nebula_spritesheet.png");
  Rectangle nebulaRec{0.0, 0.0, nebula.width / nebulaFrames, nebula.height / nebulaFrames};
  Vector2 nebulaPos{windowWidth, windowHeight - nebulaRec.height};

  // nebula animation variables
  const float nebUpdateTime{1.0 / 12.0};
  float nebRunningTime{};
  int nebFrame{};

  // nebula X velocity (pixels/seconds)
  int nebVel{-200};

  // scarfy variables
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

    // update nebula position
    nebulaPos.x += nebVel * dT;

    // update scarfy position
    scarfyPos.y += velocity * dT;

    // scarfy animation frame
    if (!isInAir)
    {
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
    }

    // nebula animation frame

    nebRunningTime += dT;

    if (nebRunningTime >= nebUpdateTime)
    {
      nebRunningTime = 0.0;

      // update animation frame
      nebulaRec.x = nebFrame * nebulaRec.width;
      nebFrame++;

      if (nebFrame > nebulaFrames - 1)
      {
        nebFrame = 0;
      }
    }

    // draw nebula
    DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);

    // draw scarfy
    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    // End Game Logic

    EndDrawing();
  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);

  // CLoses the window properly
  CloseWindow();
}
