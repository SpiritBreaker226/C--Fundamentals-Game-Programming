#include "raylib.h"

struct AnimData
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

int main()
{
  // window dimensions
  int windowDimensions[2];

  windowDimensions[0] = 512;
  windowDimensions[1] = 380;

  InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

  // acceleration due to gravity (pixels/frame)/frame
  const int gravity{1'000};

  // nebula variables

  const float nebulaFrames = 8;

  Texture2D nebula = LoadTexture("./textures/12_nebula_spritesheet.png");
  AnimData nebData{
      {0.0, 0.0, nebula.width / nebulaFrames, nebula.height / nebulaFrames},            // Rectangle rec
      {(float)windowDimensions[0], windowDimensions[1] - nebula.height / nebulaFrames}, // Vector2 pos
      0,                                                                                // int frame
      1.0 / 12.0,                                                                       // float updateTime
      0.0                                                                               // float runningTime
  };
  AnimData neb2Data{
      {0.0, 0.0, nebula.width / nebulaFrames, nebula.height / nebulaFrames},                  // Rectangle rec
      {(float)windowDimensions[0] + 300, windowDimensions[1] - nebula.height / nebulaFrames}, // Vector2 pos
      0,                                                                                      // int frame
      1.0 / 16.0,                                                                             // float updateTime
      0.0                                                                                     // float runningTime
  };
  AnimData nebulae[2]{nebData, neb2Data};

  // nebula X velocity (pixels/seconds)
  int nebVel{-200};

  // scarfy variables
  Texture2D scarfy = LoadTexture("./textures/scarfy.png");
  const int scarfyFrames = 6;
  AnimData scarfyData{};

  scarfyData.rec.width = scarfy.width / scarfyFrames;
  scarfyData.rec.height = scarfy.height;
  scarfyData.rec.x = 0;
  scarfyData.rec.y = 0;

  scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
  scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;

  scarfyData.frame = 0;
  scarfyData.runningTime = 0.0;
  scarfyData.updateTime = 1.0 / 12.0;

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
    if (scarfyData.pos.y >= (windowDimensions[1] - scarfyData.rec.height))
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
    nebulae[0].pos.x += nebVel * dT;

    // update second nebula position
    nebulae[1].pos.x += nebVel * dT;

    // update scarfy position
    scarfyData.pos.y += velocity * dT;

    // scarfy animation frame
    if (!isInAir)
    {
      // update running time
      scarfyData.runningTime += dT;

      if (scarfyData.runningTime >= scarfyData.updateTime)
      {
        scarfyData.runningTime = 0.0;

        // update animation frame
        scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
        scarfyData.frame++;

        if (scarfyData.frame > scarfyFrames - 1)
        {
          scarfyData.frame = 0;
        }
      }
    }

    // nebula animation frame

    nebulae[0].runningTime += dT;

    if (nebulae[0].runningTime >= nebulae[0].updateTime)
    {
      nebulae[0].runningTime = 0.0;

      // update animation frame
      nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
      nebulae[0].frame++;

      if (nebulae[0].frame > nebulaFrames - 1)
      {
        nebulae[0].frame = 0;
      }
    }

    // second nebula animation frame

    nebulae[1].runningTime += dT;

    if (nebulae[1].runningTime >= nebulae[1].updateTime)
    {
      nebulae[1].runningTime = 0.0;

      // update animation frame
      nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
      nebulae[1].frame++;

      if (nebulae[1].frame > nebulaFrames - 1)
      {
        nebulae[1].frame = 0;
      }
    }

    // draw nebula
    DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);

    // draw second nebula
    DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

    // draw scarfy
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

    // End Game Logic

    EndDrawing();
  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);

  // CLoses the window properly
  CloseWindow();
}
