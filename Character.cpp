#include "Character.h"

Character::Character()
{
  width = texture.width / maxFrames;
  height = texture.height;
}

Character::Character(int windowWidth, int windowHeight)
{
  width = texture.width / maxFrames;
  height = texture.height;
  screenPos = {static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
               static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)};
}

Vector2 Character::getWorldPos() { return worldPos; }

void Character::tick(float deltaTime)
{
  worldPosLastFrame = worldPos;

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
    texture = run;

    // set worldPos = worldPos + direction (or movement vector)
    // the vector in the character is reflects its position so it is a positive since
    // the character moves in the direction that the user/game wants that character to go.
    // This allows the character to apply to other non=plater characters to use the same
    // class since the world does not revolves around them.
    worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));

    rightLeft = direction.x < 0.f ? -1.f : 1.f;
  }
  else
  {
    texture = idle;
  }

  runningTime += deltaTime;

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
  Rectangle sourceRec{
      frame * width,
      0.f,
      // flips the sprite by changing the value from positive to negative and back again
      rightLeft * width,
      height};

  Rectangle destRec{
      screenPos.x,
      screenPos.y,
      scale * width,
      scale * height};

  DrawTexturePro(texture, sourceRec, destRec, Vector2{}, 0.f, WHITE);
}

void Character::undoMovement() { worldPos = worldPosLastFrame; }
