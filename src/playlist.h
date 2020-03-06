#pragma once

#include "player_exception.h"
#include "playing_mode.h"
#include "product.h"
#include <memory>
#include <random>
#include <string>
#include <vector>

class Playlist : public Playable {
  std::string name;
  std::shared_ptr<PlayingMode> playingMode;
  std::vector<PlayablePtr> elements;

  bool noCycleWhenAdding(Playable *) const override;

public:
  explicit Playlist(std::string);

  void add(const PlayablePtr &);

  void add(const PlayablePtr &, size_t);

  void remove();

  void remove(size_t);

  void setMode(std::shared_ptr<PlayingMode>);

  void play() override;
};

class OutOfBoundsException : public PlayerException {
public:
  [[nodiscard]] const char *what() const noexcept override;
};

class EmptyPlaylistException : public PlayerException {
public:
  [[nodiscard]] const char *what() const noexcept override;
};

class CycleException : public PlayerException {
public:
  [[nodiscard]] const char *what() const noexcept override;
};