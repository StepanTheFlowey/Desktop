#pragma once
#include "screen.hpp"

class Scene {
public:
  virtual int play(Screen *screen) {
    return NULL;
  }

  virtual void update() {
    return;
  }

  virtual void draw() {
    return;
  }
};

int Screen::play(Scene *scene) {
  return scene->play(this);
}