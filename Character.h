#include "raylib.h"
#include "raymath.h"

class Character
{
public:
  // constructors
  Character();
  Character(int windowWidth, int windowHeight);

  // getter and setters
  Vector2 getWorldPos();

  // public methods
  void tick(float deltaTime);
  void undoMovement();

private:
  Texture2D texture{LoadTexture("./characters/knight_idle_spritesheet.png")};
  Texture2D idle{LoadTexture("./characters/knight_idle_spritesheet.png")};
  Texture2D run{LoadTexture("./characters/knight_run_spritesheet.png")};

  Vector2 screenPos{};
  Vector2 worldPos{};
  Vector2 worldPosLastFrame{};

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
