#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) : BaseCharacter(pos,
                                                                                         idle_texture,
                                                                                         run_texture)
{
}

void Enemy::setTarget(Character *character) { target = character; }

void Enemy::tick(float deltaTime)
{
  screenPos = Vector2Subtract(worldPos, target->getWorldPos());

  BaseCharacter::tick(deltaTime);
}
