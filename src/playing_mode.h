#pragma once

#include "product.h"

class PlayingMode {
public:
  virtual std::vector<size_t> permuted(size_t);

  virtual ~PlayingMode() = default;
};

class SequenceMode : public PlayingMode {};

class OddEvenMode : public PlayingMode {
public:
  std::vector<size_t> permuted(size_t) override;
};

class ShuffleMode : public PlayingMode {
  std::default_random_engine randomEngine;

public:
  explicit ShuffleMode(uint32_t);

  std::vector<size_t> permuted(size_t) override;
};

std::shared_ptr<PlayingMode> createSequenceMode();

std::shared_ptr<PlayingMode> createOddEvenMode();

std::shared_ptr<PlayingMode> createShuffleMode(int);