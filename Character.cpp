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
  // set animation and last frame
  BaseCharacter::tick(deltaTime);

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
}
