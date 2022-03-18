#pragma once
#include "types.h"
#include "creator.hpp"
#include "screen.hpp"

//Containers
#include <unordered_map>
#include <vector>

//IO
#include <fstream>

//SFML
#include <SFML\Graphics.hpp>

class CreatorArray {
public:
  using ID_t = uint16_t;
protected:
  std::unordered_map<ID_t, Creator> creators_;
public:
  CreatorArray() {

  }

  ID_t newCreator(sf::Vector2i begin, sf::Vector2i end, gametime_t lifeTime = -1) {
    ID_t id = takeID();
    if(id == 0) {
      throw std::out_of_range("no empty id for creator ray");
    }
    Creator &creator = creators_[id];
    creator = Creator();
    creator.beginPoint = begin;
    creator.endPoint = end;
    creator.lifeTime_ = lifeTime;
    creator.deadable = lifeTime != -1;
    creator.changed = true;
    return id;
  }

  void deleteCreator(ID_t index) {
    creators_.erase(index);
  }

  void changeBeginPos(ID_t index, sf::Vector2i begin) {
    Creator &creator = creators_[index];
    creator.beginPoint = begin;
    creator.changed = true;
  }

  void changeEndPos(ID_t index, sf::Vector2i end) {
    Creator &creator = creators_[index];
    creator.endPoint = end;
    creator.changed = true;
  }

  void changeColor(ID_t index, sf::Color color) {
    Creator &creator = creators_[index];
    creator.color = color;
    creator.changed = true;
  }

  void changeWidth(ID_t index, int16_t width, int16_t targetWidth = -1, int16_t stepWidth = 0, int16_t interval = 0, bool deadable = false) {
    Creator &creator = creators_[index];
    creator.width = width;
    creator.tWidth_ = targetWidth;
    creator.sWidth_ = std::abs(stepWidth);
    creator.iWidth_ = interval;
    creator.deadable = deadable;
    creator.changed = true;
  }

  void update(gametime_t time) {
    for(auto it = std::begin(creators_); it != std::end(creators_);) {
      if(it->second.update(time)) {
        it = creators_.erase(it);
      }
      else {
        it++;
      }
    }
  }

  void draw(Screen &screen) {
    for(auto &[iKey, iVal] : creators_) {
      iVal.draw(screen);
    }
  }
protected:
  uint16_t takeID() {
    if(creators_.size() > UINT16_MAX - 3) {
      return 0;
    }

    for(ID_t i = 1; i < UINT16_MAX - 3; i++) {
      if(creators_.find(i) == creators_.end()) {
        return i;
      }
    }
    return 0;
  }
};