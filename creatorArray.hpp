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
    creators_[id] = Creator();
    creators_[id].beginPoint = begin;
    creators_[id].endPoint = end;
    creators_[id].lifeTime_ = lifeTime;
    creators_[id].lifeTimer = lifeTime != -1;
    return id;
  }

  void deleteCreator(ID_t index) {
    creators_.erase(index);
  }

  void changeBeginPos(ID_t index, sf::Vector2i begin) {
    creators_[index].beginPoint = begin;
  }

  void changeEndPos(ID_t index, sf::Vector2i end) {
    creators_[index].endPoint = end;
  }

  void changeColor(ID_t index, sf::Color color) {
    creators_[index].color = color;
  }

  void changeWidth(ID_t index, int16_t width, int16_t targetWidth = -1, int16_t stepWidth = 0, int16_t interval = 0) {
    creators_[index].width = width;
    creators_[index].tWidth_ = targetWidth;
    creators_[index].sWidth_ = std::abs(stepWidth);
    creators_[index].iWidth_ = interval;
  }

  void update(gametime_t time) {
    for(auto it = std::begin(creators_); it != std::end(creators_);) {
      if(!it->second.update(time)) {
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