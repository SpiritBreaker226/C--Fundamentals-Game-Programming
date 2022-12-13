#include "raylib.h"

class Enemy
{
public:
  // constructors
  Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);

  // getter and setters
  Vector2 getWorldPos();

  // public methods
  Rectangle getCollisionRec();
  void tick(float deltaTime);
  void undoMovement();

private:
  Vector2 screenPos{};
  Vector2 worldPos{};
  Vector2 worldPosLastFrame{};

  Texture2D texture{};
  Texture2D idle{};
  Texture2D run{};

  float width{};
  float height{};

  float rightLeft{1.f};
  float scale{4.f};

  // animation variables
  float runningTime{};
  float updateTime{1.f / 12.f};
  float speed{4.f};
  float frame{};
  int maxFrames{6};
};
