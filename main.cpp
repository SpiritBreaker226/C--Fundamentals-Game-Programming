#include "raylib.h"

struct AnimData
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
  return data.pos.y >= (windowHeight - data.rec.height);
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
  // update running time
  data.runningTime += deltaTime;

  if (data.runningTime >= data.updateTime)
  {
    data.runningTime = 0.0;

    // update animation frame
    data.rec.x = data.frame * data.rec.width;
    data.frame++;

    if (data.frame > maxFrame)
    {
      data.frame = 0;
    }
  }

  return data;
}

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

  Texture2D nebula = LoadTexture("./textures/12_nebula_spritesheet.png");

  const int nebulaMaxFrames = 8;
  const int sizeOfNebulae = 6;
  const int nebulaSpaceBetween = 300;
  AnimData nebulae[sizeOfNebulae]{};

  for (int index = 0; index < sizeOfNebulae; index++)
  {
    nebulae[index].rec.x = 0.0;
    nebulae[index].rec.y = 0.0;
    nebulae[index].rec.width = nebula.width / nebulaMaxFrames;
    nebulae[index].rec.height = nebula.height / nebulaMaxFrames;
    nebulae[index].pos.y = windowDimensions[1] - nebula.height / nebulaMaxFrames;
    nebulae[index].frame = 0;
    nebulae[index].runningTime = 0.0;
    nebulae[index].updateTime = 0.0;
    nebulae[index].pos.x = windowDimensions[0] + index * nebulaSpaceBetween;
  }

  // nebula X velocity (pixels/seconds)
  int nebVel{-200};

  // scarfy variables
  Texture2D scarfy = LoadTexture("./textures/scarfy.png");
  const int scarfyMaxFrames = 6;
  AnimData scarfyData{};

  scarfyData.rec.width = scarfy.width / scarfyMaxFrames;
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

  Texture2D background = LoadTexture("./textures/far-buildings.png");
  float bgX{};

  Texture2D midBackground = LoadTexture("./textures/back-buildings.png");
  float mgX{};

  Texture2D foreBackground = LoadTexture("./textures/foreground.png");
  float fgX{};

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    // delta time (time since last frame)
    const float dT{GetFrameTime()};

    BeginDrawing();

    ClearBackground(WHITE);

    // Start Game Logic

    bgX -= 20 * dT;

    if (bgX <= -background.width * 2)
    {
      bgX = 0.0;
    }

    Vector2 bg1Pos{bgX, 0.0};
    DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
    Vector2 bg2Pos{bgX + background.width * 2, 0.0};
    DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

    mgX -= 40 * dT;

    if (mgX <= -midBackground.width * 2)
    {
      mgX = 0.0;
    }

    Vector2 mg1Pos{mgX, 0.0};
    DrawTextureEx(midBackground, mg1Pos, 0.0, 2.0, WHITE);
    Vector2 mg2Pos{mgX + midBackground.width * 2, 0.0};
    DrawTextureEx(midBackground, mg2Pos, 0.0, 2.0, WHITE);

    fgX -= 80 * dT;

    if (fgX <= -foreBackground.width * 2)
    {
      fgX = 0.0;
    }

    Vector2 fg1Pos{fgX, 0.0};
    DrawTextureEx(foreBackground, fg1Pos, 0.0, 2.0, WHITE);
    Vector2 fg2Pos{fgX + foreBackground.width * 2, 0.0};
    DrawTextureEx(foreBackground, fg2Pos, 0.0, 2.0, WHITE);

    // perform ground check
    if (isOnGround(scarfyData, windowDimensions[1]))
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
      scarfyData = updateAnimData(scarfyData, dT, scarfyMaxFrames - 1);
    }

    for (int index = 0; index < sizeOfNebulae; index++)
    {
      nebulae[index] = updateAnimData(nebulae[index], dT, nebulaMaxFrames - 1);
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
  UnloadTexture(background);
  UnloadTexture(midBackground);
  UnloadTexture(foreBackground);

  // CLoses the window properly
  CloseWindow();
}
