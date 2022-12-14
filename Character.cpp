#include "Character.h"

Character::Character(int windowWidth, int windowHeight) : BaseCharacter(
                                                              Vector2{},
                                                              LoadTexture("./characters/knight_idle_spritesheet.png"),
                                                              LoadTexture("./characters/knight_run_spritesheet.png"))
{
  screenPos = {static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
               static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)};
}

Vector2 Character::getScreenPos() { return screenPos; }

void Character::tick(float deltaTime)
{
  if (IsKeyDown(KEY_A))
    velocity.x -= 1.0;
  if (IsKeyDown(KEY_D))
    velocity.x += 1.0;
  if (IsKeyDown(KEY_W))
    velocity.y -= 1.0;
  if (IsKeyDown(KEY_S))
    velocity.y += 1.0;

  // set animation and last frame
  BaseCharacter::tick(deltaTime);
}
