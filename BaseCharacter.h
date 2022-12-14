#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"
#include "raymath.h"

class BaseCharacter
{
public:
  BaseCharacter();
  BaseCharacter(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);

  // getter and setters
  Vector2 getWorldPos() const { return worldPos; };
  bool getAlive() const { return alive; };
  void setAlive(bool isAlive) { alive = isAlive; };

  // public methods
  Rectangle getCollisionRec();
  virtual Vector2 getScreenPos() = 0;
  virtual void tick(float deltaTime);
  void undoMovement();

protected:
  Vector2 worldPos{};
  Vector2 worldPosLastFrame{};

  Texture2D texture{LoadTexture("./characters/knight_idle_spritesheet.png")};
  Texture2D idle{LoadTexture("./characters/knight_idle_spritesheet.png")};
  Texture2D run{LoadTexture("./characters/knight_run_spritesheet.png")};

  float width{};
  float height{};

  float rightLeft{1.f};
  float scale{4.f};

  // animation variables
  float runningTime{};
  float updateTime{1.f / 12.f};
  float speed{4.f};
  Vector2 velocity{};
  float frame{};
  int maxFrames{6};

private:
  bool alive{true};
};

#endif
