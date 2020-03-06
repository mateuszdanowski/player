#include "product.h"
#include <regex>
#include <sstream>

bool Product::checkContent(const std::string &content) {
  static std::regex contentRegex(R"([a-zA-Z\d\s,.!?':;-]*)");
  return std::regex_match(content, contentRegex);
}

bool Song::checkMetaData(MetaData metaData) {
  auto requiredMetaData = getRequiredMetaData();

  for (const auto &it : metaData) {
    if (requiredMetaData.find(it.first) == requiredMetaData.end()) {
      return false;
    }
  }
  return true;
}

bool Movie::checkMetaData(MetaData metaData) {
  auto requiredMetaData = getRequiredMetaData();

  for (const auto &it : metaData) {
    if (requiredMetaData.find(it.first) == requiredMetaData.end()) {
      return false;
    }
  }
  return true;
}

std::unordered_map<std::string, Product *> &
ProductFactory::registeredProducts() {
  static std::unordered_map<std::string, Product *> registeredProducts;
  return registeredProducts;
}

void ProductFactory::registerProduct(const std::string &productID, Product *p) {
  registeredProducts().insert({productID, p});
}

std::shared_ptr<Product>
ProductFactory::getMatchingProduct(const std::string &productID,
                                   const MetaData &metaData) {
  if (registeredProducts().find(productID) == registeredProducts().end()) {
    throw ProductException(
        UnsupportedTypeException().what()); // unsupported type
  }
  try {
    return registeredProducts()[productID]->createProduct(metaData);
  } catch (const IncorrectMetaDataException &e) {
    throw ProductException(e.what()); // corrupt file
  } catch (const CorruptContentException &e) {
    throw ProductException(e.what()); // corrupt content
  }
}

std::shared_ptr<Product> Song::createProduct(MetaData metaData) {
  if (!checkMetaData(metaData)) {
    throw IncorrectMetaDataException(); // corrupt file
  }
  if (!checkContent(metaData["__content"])) {
    throw CorruptContentException(); // corrupt content
  }
  return std::make_shared<Song>(metaData);
}

std::string &Song::getName() {
  static std::string name = "Song";
  return name;
}

Song &Song::dummy() {
  static Song dummy;
  return dummy;
}

void Song::registerToFactory() {
  dummy() = Song();
  ProductFactory::registerProduct("audio", &dummy());
}

std::unordered_set<std::string> &Song::getRequiredMetaData() {
  static std::unordered_set<std::string> requiredMetaData = {"artist", "title",
                                                             "__content"};
  return requiredMetaData;
}

void Song::play() {
  std::stringstream ss;
  ss << getName() << " ";
  ss << "[";
  ss << metaData["artist"] << ", ";
  ss << metaData["title"];
  ss << "]: ";
  ss << metaData["__content"];
  ss << "\n";
  std::cout << ss.str();
}

namespace { // utils
std::string ROT13(const std::string &source) {
  std::string transformed;
  for (char c : source) {
    if (isalpha(c)) {
      if (tolower(c) - 'a' < 13) {
        transformed.push_back(c + 13);
      } else {
        transformed.push_back(c - 13);
      }
    } else {
      transformed.push_back(c);
    }
  }
  return transformed;
}

bool checkYear(const std::string &year) {
  static std::regex yearRegex(R"(\d+)");
  return std::regex_match(year, yearRegex);
}
} // namespace

std::shared_ptr<Product> Movie::createProduct(MetaData metaData) {
  if (!checkMetaData(metaData)) {
    throw IncorrectMetaDataException(); // corrupt file
  }
  if (!checkContent(ROT13(metaData["__content"]))) {
    throw CorruptContentException(); // corrupt content
  }
  if (!checkYear(metaData["year"])) {
    throw CorruptContentException();
  }

  return std::make_shared<Movie>(metaData);
}

std::string &Movie::getName() {
  static std::string name = "Movie";
  return name;
}

Movie &Movie::dummy() {
  static Movie dummy;
  return dummy;
}

void Movie::registerToFactory() {
  dummy() = Movie();
  ProductFactory::registerProduct("video", &dummy());
}

std::unordered_set<std::string> &Movie::getRequiredMetaData() {
  static std::unordered_set<std::string> requiredMetaData = {"title", "year",
                                                             "__content"};
  return requiredMetaData;
}

void Movie::play() {
  std::stringstream ss;
  ss << getName() << " ";
  ss << "[";
  ss << metaData["title"] << ", ";
  ss << metaData["year"];
  ss << "]: ";
  ss << ROT13(metaData["__content"]);
  ss << "\n";
  std::cout << ss.str();
}

const char *UnsupportedTypeException::what() const noexcept {
  return "unsupported type";
}

const char *IncorrectMetaDataException::what() const noexcept {
  return "incorrect metadata";
}

const char *CorruptContentException::what() const noexcept {
  return "corrupt content";
}