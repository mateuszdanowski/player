#include "file.h"
#include "product.h"
#include <unordered_set>
#include <vector>

std::shared_ptr<Playable> File::validate(File &file) {
  static const char delimiter = '|';
  static const char separator = ':';

  std::string s = file.description;

  size_t start = 0;
  size_t end = s.find(delimiter);

  if (end == std::string::npos) {
    throw FileException(); // corrupt file
  }

  std::string fileType = s.substr(start, end - start);

  std::vector<std::string> elementsToValidate;
  while (end != std::string::npos) {
    start = end + 1;
    end = s.find(delimiter, start);
    elementsToValidate.push_back(s.substr(start, end - start));
  }

  std::unordered_map<std::string, std::string> elements;
  for (size_t i = 0; i < elementsToValidate.size(); i++) {
    std::string element = elementsToValidate[i];

    if (i == elementsToValidate.size() - 1) {
      elements.insert({"__content", element});
    } else {
      size_t separatorPos = element.find(separator);
      if (separatorPos == std::string::npos) {
        throw FileException(); // corrupt file
      } else {
        std::string name = element.substr(0, separatorPos);
        std::string value = element.substr(separatorPos + 1, std::string::npos);

        if (elements.find(name) != elements.end()) {
          elements.erase(elements.find(name));
        }
        elements.insert({name, value});
      }
    }
  }

  try {
    return ProductFactory::getMatchingProduct(fileType, elements);
  } catch (const ProductException &e) {
    throw FileException(
        e.what()); // corrupt content or corrupt file or unsupported type
  }
}

File::File(const std::string &description) { this->description = description; }