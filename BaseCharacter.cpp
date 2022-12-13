#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{
  width = texture.width / maxFrames;
  height = texture.height;
}

BaseCharacter::BaseCharacter(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) : worldPos(pos),
                                                                                           texture(idle_texture),
                                                                                           idle(idle_texture),
                                                                                           run(run_texture)
{
  width = texture.width / maxFrames;
  height = texture.height;
}

Vector2 BaseCharacter::getWorldPos() { return worldPos; }

Rectangle BaseCharacter::getCollisionRec()
{
  return Rectangle{
      screenPos.x,
      screenPos.y,
      scale * width,
      scale * height,
  };
}

void BaseCharacter::tick(float deltaTime)
{
  worldPosLastFrame = worldPos;

  // update animation frame
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

void BaseCharacter::undoMovement() { worldPos = worldPosLastFrame; }
