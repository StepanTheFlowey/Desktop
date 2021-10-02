#pragma once

#include "types.h"

#include <map>

#include <SFML\Graphics.hpp>

class Textures {
  std::map<std::wstring, sf::Image> images_;
  std::map<std::wstring, sf::Texture> textures_;
public:
  Textures() {

  }

  void load() {

  }

  void save() {

  }

  inline void clearAll() {
    clearImages();
    clearTextures();
  }

  inline void clearImages() {
    images_.clear();
  }

  inline void clearTextures() {
    textures_.clear();
  }

  sf::Texture &getTexture(std::wstring name) {
    if(textures_.find(name) == textures_.end()) {
      throw std::out_of_range("texture does not load");
    }
    return textures_[name];
  }
};