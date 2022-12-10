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

  const int sizeOfNebulae = 6;
  const int nebulaSpaceBetween = 300;
  AnimData nebulae[sizeOfNebulae]{};

  for (int index = 0; index < sizeOfNebulae; index++)
  {
    nebulae[index].rec.x = 0.0;
    nebulae[index].rec.y = 0.0;
    nebulae[index].rec.width = nebula.width / nebulaFrames;
    nebulae[index].rec.height = nebula.height / nebulaFrames;
    nebulae[index].pos.y = windowDimensions[1] - nebula.height / nebulaFrames;
    nebulae[index].frame = 0;
    nebulae[index].runningTime = 0.0;
    nebulae[index].updateTime = 0.0;
    nebulae[index].pos.x = windowDimensions[0] + index * nebulaSpaceBetween;
  }

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

    for (int index = 0; index < sizeOfNebulae; index++)
    {
      // update each nebula position
      nebulae[index].pos.x += nebVel * dT;
    }

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

    for (int index = 0; index < sizeOfNebulae; index++)
    {
      // nebula animation frame
      nebulae[index].runningTime += dT;

      if (nebulae[index].runningTime >= nebulae[index].updateTime)
      {
        nebulae[index].runningTime = 0.0;

        // update animation frame
        nebulae[index].rec.x = nebulae[index].frame * nebulae[index].rec.width;
        nebulae[index].frame++;

        if (nebulae[index].frame > nebulaFrames - 1)
        {
          nebulae[index].frame = 0;
        }
      }
    }

    for (int index = 0; index < sizeOfNebulae; index++)
    {
      // draw nebula
      DrawTextureRec(nebula, nebulae[index].rec, nebulae[index].pos, WHITE);
    }

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
