#pragma once

#include "file.h"
#include "playlist.h"

class Player {
public:
  Player();

  std::shared_ptr<Playable> openFile(File);

  std::shared_ptr<Playlist> createPlaylist(const std::string &);
};
