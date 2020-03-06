#pragma once

#include <memory>

class Playable {
public:
  virtual ~Playable() = default;

  virtual void play() = 0;

  virtual bool noCycleWhenAdding(Playable *) const;
};

using PlayablePtr = std::shared_ptr<Playable>;