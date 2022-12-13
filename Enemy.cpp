#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) : BaseCharacter(pos,
                                                                                         idle_texture,
                                                                                         run_texture)
{
}

void Enemy::tick(float deltaTime)
{
  BaseCharacter::tick(deltaTime);
}
