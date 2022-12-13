#include "raylib.h"

class Prop
{
public:
  // constructors
  Prop(Vector2 pos, Texture2D tex);

private:
  Vector2 worldPos{};
  Texture2D texture{};
  float scale{4.f};
};
