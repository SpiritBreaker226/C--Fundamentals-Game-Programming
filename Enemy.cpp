#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) : BaseCharacter(pos,
                                                                                         idle_texture,
                                                                                         run_texture)
{
  speed = 3.5f;
}

Vector2 Enemy::getScreenPos()
{
  return Vector2Subtract(worldPos, target->getWorldPos());
}

void Enemy::setTarget(Character *character) { target = character; }

void Enemy::tick(float deltaTime)
{
  if (!getAlive())
    return;

  velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

  if (Vector2Length(velocity) < radius)
  {
    velocity = Vector2{};
  }

  BaseCharacter::tick(deltaTime);

  if (CheckCollisionRecs(getCollisionRec(), target->getCollisionRec()))
  {
    target->takeDamage(damagePerSecond * deltaTime);
  }
}
