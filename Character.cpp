#include "Character.h"

Character::Character(int winWidth, int winHeight) : windowWidth(winWidth), windowHeight(winHeight)
{
}

Vector2 Character::getScreenPos()
{
  return Vector2{static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
                 static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)};
}

void Character::takeDamage(float damage)
{
  health -= damage;

  if (health <= 0.f)
  {
    setAlive(false);
  }
}

void Character::tick(float deltaTime)
{
  if (!getAlive())
    return;

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

  Vector2 weaponOrigin{};
  Vector2 weaponOffset{};
  float weaponRotation{};

  if (rightLeft > 0.f)
  {
    weaponOrigin = {0.f, weapon.height * scale};
    weaponOffset = {35.f, 55.f};
    weaponCollisionRec = {
        getScreenPos().x + weaponOffset.x,
        getScreenPos().y + weaponOffset.y - weapon.height * scale,
        weapon.width * scale,
        weapon.height * scale};

    weaponRotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.f : 0.f;
  }
  else
  {
    weaponOrigin = {weapon.width * scale, weapon.height * scale};
    weaponOffset = {25.f, 55.f};
    weaponCollisionRec = {
        getScreenPos().x + weaponOffset.x - weapon.width * scale,
        getScreenPos().y + weaponOffset.y - weapon.height * scale,
        weapon.width * scale,
        weapon.height * scale};

    weaponRotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.f : 0.f;
  }

  // draw the sword
  Rectangle weaponSource{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
  Rectangle weaponDest{getScreenPos().x + weaponOffset.x, getScreenPos().y + weaponOffset.y, weapon.width * scale, weapon.height * scale};

  DrawTexturePro(weapon, weaponSource, weaponDest, weaponOrigin, weaponRotation, WHITE);
}
