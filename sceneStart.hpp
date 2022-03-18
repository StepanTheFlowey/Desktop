#pragma once
#include "scene.hpp"

//SFML
#include <SFML\Graphics.hpp>

class SceneStart : public Scene {
  Screen *screen_ = nullptr;
  sf::Color backgroundColor;
  uint8_t i = 0;
  bool work_ = true;
public:
  SceneStart() {

  }

  virtual int play(Screen *screen) override {
    screen_ = screen;
    i = 100;
    while(work_) {
      screen_->ignoreEvents();
      update();
      draw();
    }
    return 0;
  }

  virtual void update() override {
    i -= 2;
    if(i == 0) {
      work_ = false;
    }
    backgroundColor = sf::Color(i, i, i, 0);
  }

  virtual void draw() override {
    screen_->window.clear(backgroundColor);
    screen_->window.display();
  }
};