#include "utils.h"

/*
 * Interpret ruby's negative string indices.
 * If a value out of bounds is given, return length+1,
 * which should point caller to a null character.
 */
int
_string_position(int position, int length)
{
  if (position > 0) {
    if (position > length) {
      position = length+1;
    }
  } else { // position is negative. 
    position += length;
    if (position < 0) {
      position = length+1;
    }
  }
  return position;
}
