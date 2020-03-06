#include "playlist.h"
#include <sstream>

Playlist::Playlist(std::string name)
    : name(std::move(name)), playingMode(createSequenceMode()) {}

void Playlist::setMode(std::shared_ptr<PlayingMode> modePtr) {
  playingMode = std::move(modePtr);
}

void Playlist::add(const PlayablePtr &son) {
  if (son->noCycleWhenAdding(this))
    elements.push_back(son);
  else
    throw CycleException();
}

void Playlist::add(const PlayablePtr &son, size_t pos) {
  if (elements.size() < pos)
    throw OutOfBoundsException();

  if (son->noCycleWhenAdding(this))
    elements.insert(elements.begin() + pos, son);
  else
    throw CycleException();
}

void Playlist::remove() {
  if (elements.empty())
    throw EmptyPlaylistException();
  elements.pop_back();
}

void Playlist::remove(size_t pos) {
  if (pos < elements.size())
    elements.erase(elements.begin() + pos);
  else
    throw OutOfBoundsException();
}

void Playlist::play() {
  std::stringstream ss;
  ss << "Playlist"
     << " ";
  ss << "[";
  ss << name;
  ss << "]";
  ss << "\n";
  std::cout << ss.str();

  for (size_t index : playingMode->permuted(elements.size()))
    elements[index]->play();
}

bool Playlist::noCycleWhenAdding(Playable *parent) const {
  if (parent == this)
    return false;
  for (const auto &el : elements) {
    if (!el->noCycleWhenAdding(parent))
      return false;
  }
  return true;
}

const char *OutOfBoundsException::what() const noexcept {
  static constexpr std::string_view beyond_msg =
      "trying to access elements after the end of the playlist";
  return beyond_msg.data();
}

const char *EmptyPlaylistException::what() const noexcept {
  static constexpr std::string_view empty_msg =
      "trying to remove from an empty playlist";
  return empty_msg.data();
}

const char *CycleException::what() const noexcept {
  static constexpr std::string_view cycle_msg =
      "cannot add to playlist: cycle detected";
  return cycle_msg.data();
}
