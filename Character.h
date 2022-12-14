#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "raymath.h"

#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
  // constructors
  Character(int windowWidth, int windowHeight);

  // public methods
  virtual void tick(float deltaTime) override;

private:
};

#endif
