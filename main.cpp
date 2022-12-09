#include "raylib.h"

int main(int argc, const char **argv)
{
  // false
  bool equal{4 == 9};

  // true
  bool not_equal{4 != 9};

  // true
  bool less{4 < 9};

  // false
  bool greater{4 > 9};

  // true
  bool lest_equal{4 <= 9};

  // false
  bool greater_equal{4 >= 9};

  int width = 350;

  // create a window
  InitWindow(width, 900, "Jason Stathopulos");

  return 0;
}
