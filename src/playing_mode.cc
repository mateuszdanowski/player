#include "playing_mode.h"
#include <algorithm>
#include <random>

std::shared_ptr<PlayingMode> createSequenceMode() {
  return std::make_shared<SequenceMode>();
}

std::shared_ptr<PlayingMode> createOddEvenMode() {
  return std::make_shared<OddEvenMode>();
}

std::shared_ptr<PlayingMode> createShuffleMode(int seed) {
  return std::make_shared<ShuffleMode>(seed);
}

std::vector<size_t> PlayingMode::permuted(size_t permutation_len) {
  std::vector<size_t> res(permutation_len);
  std::iota(res.begin(), res.end(), 0);
  return res;
}

std::vector<size_t> OddEvenMode::permuted(size_t permutation_len) {
  std::vector<size_t> perm(permutation_len);
  size_t idx = 0;
  for (int beg = 1; beg >= 0; --beg)
    for (size_t i = beg; i < permutation_len; i += 2)
      perm[idx++] = i;
  return perm;
}

ShuffleMode::ShuffleMode(uint32_t seed) : randomEngine(seed) {}

std::vector<size_t> ShuffleMode::permuted(size_t permutation_len) {
  auto perm = PlayingMode::permuted(permutation_len);
  std::shuffle(perm.begin(), perm.end(), randomEngine);
  return perm;
}
