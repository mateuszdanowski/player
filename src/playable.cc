#include "playable.h"

bool Playable::noCycleWhenAdding(Playable *parent) const {
  return parent != this;
}