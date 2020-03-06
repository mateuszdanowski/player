#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "playable.h"

using MetaData = std::unordered_map<std::string, std::string>;

class Product : public Playable {
protected:
  std::unordered_map<std::string, std::string> metaData;

  virtual bool checkMetaData(MetaData metaData) = 0;

  static bool checkContent(const std::string &content);

public:
  Product() = default;

  explicit Product(MetaData metaData) : metaData(std::move(metaData)) {}

  virtual std::shared_ptr<Product> createProduct(MetaData) = 0;
};

class ProductFactory {
  static std::unordered_map<std::string, Product *> &registeredProducts();

public:
  static void registerProduct(const std::string &productID, Product *p);

  static std::shared_ptr<Product>
  getMatchingProduct(const std::string &productID, const MetaData &metaData);
};

class Song : public Product {
  bool checkMetaData(MetaData metaData) override;

  static std::string &getName();

  static std::unordered_set<std::string> &getRequiredMetaData();

  static Song &dummy();

  std::shared_ptr<Product> createProduct(MetaData metaData) override;

public:
  Song() = default;

  explicit Song(MetaData metaData) : Product(std::move(metaData)) {}

  static void registerToFactory();

  void play() override;
};

class Movie : public Product {
  bool checkMetaData(MetaData metaData) override;

  static std::string &getName();

  static std::unordered_set<std::string> &getRequiredMetaData();

  static Movie &dummy();

  std::shared_ptr<Product> createProduct(MetaData metaData) override;

public:
  Movie() = default;

  explicit Movie(MetaData metaData) : Product(std::move(metaData)) {}

  static void registerToFactory();

  void play() override;
};

class ProductException : public std::exception {
protected:
  std::string msg;

public:
  ProductException() { msg = "Product Exception"; }

  explicit ProductException(const char *msg) { this->msg = msg; }

  explicit ProductException(const std::string &msg) { this->msg = msg; }

  [[nodiscard]] const char *what() const noexcept override {
    return msg.c_str();
  }
};

class UnsupportedTypeException : ProductException {
public:
  [[nodiscard]] const char *what() const noexcept override;
};

class IncorrectMetaDataException : ProductException {
public:
  [[nodiscard]] const char *what() const noexcept override;
};

class CorruptContentException : ProductException {
public:
  [[nodiscard]] const char *what() const noexcept override;
};