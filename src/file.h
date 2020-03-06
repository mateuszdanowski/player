#pragma once

#include "product.h"
#include <string>

class File {
  std::string description;

public:
  static std::shared_ptr<Playable> validate(File &);

  explicit File(const std::string &);
};

class FileException : public std::exception {
protected:
  std::string msg;

public:
  FileException() { msg = "corrupt file"; }

  explicit FileException(const char *msg) { this->msg = msg; }

  explicit FileException(const std::string &msg) { this->msg = msg; }

  [[nodiscard]] const char *what() const noexcept override {
    return msg.c_str();
  }
};