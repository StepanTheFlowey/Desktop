#pragma once
#include "screen.hpp"

class Scene {
public:
  virtual int16_t getState() {
    return NULL;
  }

  virtual void play(Screen *screen) {
    return;
  }

  virtual void update() {
    return;
  }

  virtual void draw() {
    return;
  }
};

void Screen::play(Scene *scene) {
  scene->play(this);
}