#include <exception>
#include <string>

class PlayerException : public std::exception {
protected:
  std::string msg;

public:
  PlayerException() { msg = "player exception"; }

  explicit PlayerException(const char *msg) { this->msg = msg; }

  explicit PlayerException(const std::string &msg) { this->msg = msg; }

  [[nodiscard]] const char *what() const noexcept override {
    return msg.c_str();
  }
};