#include "raylib.h"
#include "raymath.h"

class Prop
{
public:
  // constructors
  Prop(Vector2 pos, Texture2D tex);

  // public method
  void Render(Vector2 characterPos);

private:
  Vector2 worldPos{};
  Texture2D texture{};
  float scale{4.f};
};
