#include "player.h"
#include "file.h"
#include "product.h"

Player::Player() {
  Song::registerToFactory();
  Movie::registerToFactory();
}

std::shared_ptr<Playable> Player::openFile(File file) {
  try {
    return File::validate(file);
  } catch (const FileException &e) {
    throw PlayerException(e.what());
  }
}

std::shared_ptr<Playlist> Player::createPlaylist(const std::string &name) {
  return std::make_shared<Playlist>(name);
}