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
      getScreenPos().x,
      getScreenPos().y,
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
      getScreenPos().x,
      getScreenPos().y,
      scale * width,
      scale * height};

  if (Vector2Length(velocity) != 0.0)
  {
    texture = run;

    // set worldPos = worldPos + velocity (or movement vector)
    // the vector in the character is reflects its position so it is a positive since
    // the character moves in the velocity that the user/game wants that character to go.
    // This allows the character to apply to other non=plater characters to use the same
    // class since the world does not revolves around them.
    worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

    rightLeft = velocity.x < 0.f ? -1.f : 1.f;
  }
  else
  {
    texture = idle;
  }

  // resets the velocity so that it does not add or subtract
  // in either player or NPC classes since it must be 1 or -1
  velocity = {};

  DrawTexturePro(texture, sourceRec, destRec, Vector2{}, 0.f, WHITE);
}

void BaseCharacter::undoMovement() { worldPos = worldPosLastFrame; }
