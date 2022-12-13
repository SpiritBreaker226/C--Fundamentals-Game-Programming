#include "Prop.h"

Prop::Prop(Vector2 pos, Texture2D tex) : worldPos(pos), texture(tex)
{
}

void Prop::Render(Vector2 characterPos)
{
  Vector2 screenPos{Vector2Subtract(worldPos, characterPos)};

  DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}
