#pragma once
#include "scene.hpp"

//SFML
#include <SFML\Graphics.hpp>

class SceneStart : public Scene {
  bool work_ = true;
  Screen *screen_ = nullptr;
  uint8_t i = 0;
public:
  SceneStart() {

  }

  virtual void play(Screen *screen) override {
    screen_ = screen;
    i = 100;
    while(work_) {
      screen_->ignoreEvents();
      update();
      draw();
    }
  }

  virtual void update() override {
    i -= 2;
    if(i == 0) {
      work_ = false;
    }
    screen_->clearColor = sf::Color(i, i, i, 0);
  }

  virtual void draw() override {
    screen_->clear();
    screen_->display();
  }
};