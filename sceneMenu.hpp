#pragma once
#include "scene.hpp"

//SFML
#include <SFML\Graphics.hpp>

class SceneMenu : public Scene {
  Screen *screen_ = nullptr;
  bool work_ = true;

  bool baDir = true;
  uint8_t baValue = 0;
  uint8_t baCounter = 0;

  bool open = false;
  uint8_t openStage = 0;
  uint8_t openCounter = 0;
  gametime_t timeElapsed = 0;

  sf::Vertex vertex[64];
  sf::FloatRect rects[4];
  bool selects[4];

  sf::Clock clock;
  CreatorArray creators;
  gametime_t gametime = 0;
public:
  SceneMenu() {
    uint16_t width = sf::VideoMode::getDesktopMode().width / 6;
    for(uint8_t i = 0; i < 4; i++) {
      selects[i] = false;
      rects[i].height = 250;
      rects[i].width = 250;
      rects[i].top = 500;
      rects[i].left = width * (i + 1);
    }
    uint8_t index;
    for(uint8_t i = 0; i < 4; i++) {
      index = i * 16;
      vertex[index + 0].position = sf::Vector2f(rects[i].left, rects[i].top);
      vertex[index + 1].position = sf::Vector2f(rects[i].left, rects[i].top + 5);
      vertex[index + 2].position = sf::Vector2f(rects[i].left + rects[i].width, rects[i].top + 5);
      vertex[index + 3].position = sf::Vector2f(rects[i].left + rects[i].width, rects[i].top);

      vertex[index + 4].position = sf::Vector2f(rects[i].left + rects[i].width, rects[i].top + 5);
      vertex[index + 5].position = sf::Vector2f(rects[i].left + rects[i].width - 5, rects[i].top + 5);
      vertex[index + 6].position = sf::Vector2f(rects[i].left + rects[i].width - 5, rects[i].top + rects[i].height - 5);
      vertex[index + 7].position = sf::Vector2f(rects[i].left + rects[i].width, rects[i].top + rects[i].height - 5);

      vertex[index + 8].position = sf::Vector2f(rects[i].left, rects[i].top + rects[i].height - 5);
      vertex[index + 9].position = sf::Vector2f(rects[i].left, rects[i].top + rects[i].height);
      vertex[index + 10].position = sf::Vector2f(rects[i].left + rects[i].width, rects[i].top + rects[i].height);
      vertex[index + 11].position = sf::Vector2f(rects[i].left + rects[i].width, rects[i].top + rects[i].height - 5);

      vertex[index + 12].position = sf::Vector2f(rects[i].left, rects[i].top + rects[i].height - 5);
      vertex[index + 13].position = sf::Vector2f(rects[i].left + 5, rects[i].top + rects[i].height - 5);
      vertex[index + 14].position = sf::Vector2f(rects[i].left + 5, rects[i].top + 5);
      vertex[index + 15].position = sf::Vector2f(rects[i].left, rects[i].top + 5);

    }
  }

  virtual void play(Screen *screen) override {
    screen_ = screen;
    screen_->vertexBuffers.emplace_back();
    screen_->vertexBuffers.back().setPrimitiveType(sf::Quads);
    screen_->vertexBuffers.back().setUsage(sf::VertexBuffer::Stream);
    screen_->vertexBuffers.back().create(64);
    screen_->clearColor = sf::Color(0, 0, 0, 0);

    for(uint8_t i = 0; i < 64; i++) {
      vertex[i].color = sf::Color(0, 255, 0, 255);
    }

    clock.restart();
    while(work_) {
      gametime = clock.restart().asMilliseconds();
      //std::wcout << gametime << std::endl;
      screen_->ignoreEvents();
      /*while(screen_->precessEvent()) {
        switch(screen_->event.type) {
          case sf::Event::Closed:
          {
            if(open) {
              close_ = true;
            }
          }
        }
      }*/
      update();
      draw();
    }
  }

  virtual void update() override {
    if(!open) {
      timeElapsed += gametime;
      if(timeElapsed > 100) {
        timeElapsed -= 100;
        const uint8_t index = openStage * 16;
        switch(openCounter) {
          case 0:
          {
            creators.changeWidth(creators.newCreator(getRandomCreatorBeginPos<int>(), sf::Vector2i(rects[openStage].left, rects[openStage].top), -1), 10, 0, 1, 50);
            break;
          }
          case 1:
          {
            creators.changeWidth(creators.newCreator(getRandomCreatorBeginPos<int>(), sf::Vector2i(rects[openStage].left + rects[openStage].width, rects[openStage].top), -1), 10, 0, 1, 50);
            screen_->vertexBuffers.back().update(vertex + index, 4, index + 0);
            break;
          }
          case 3:
          {
            creators.changeWidth(creators.newCreator(getRandomCreatorBeginPos<int>(), sf::Vector2i(rects[openStage].left + rects[openStage].width, rects[openStage].top + rects[openStage].height), -1), 10, 0, 1, 50);
            screen_->vertexBuffers.back().update(vertex + index + 4, 4, index + 4);
            break;
          }
          case 4:
          {
            creators.changeWidth(creators.newCreator(getRandomCreatorBeginPos<int>(), sf::Vector2i(rects[openStage].left, rects[openStage].top + rects[openStage].height), -1), 10, 0, 1, 50);
            screen_->vertexBuffers.back().update(vertex + index + 8, 4, index + 8);
            break;
          }
          case 5:
          {
            creators.changeWidth(creators.newCreator(getRandomCreatorBeginPos<int>(), sf::Vector2i(rects[openStage].left, rects[openStage].top), -1), 10, 0, 1, 50);
            screen_->vertexBuffers.back().update(vertex + index + 12, 4, index + 12);
            openStage++;
            openCounter = UINT8_MAX;
            if(openStage == 4) {
              open = true;
            }
            break;
          }
        }
        openCounter++;
      }
    }
    else {
      baCounter++;
      if(baCounter == 3) {
        baCounter = 0;
        if(baDir) {
          baValue++;
          if(baValue > 64) {
            baDir = false;
          }
        }
        else {
          baValue--;
          if(baValue == 0) {
            baDir = true;
          }
        }
        screen_->clearColor = sf::Color(0, 0, 0, baValue);
      }
      const sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition());
      for(uint8_t i = 0; i < 4; i++) {
        if(rects[i].contains(mousePos)) {
          if(!selects[i]) {
            for(uint8_t j = 0; j < 16; j++) {
              vertex[i * 16 + j].color = sf::Color(255, 255, 255, 255);
            }
            screen_->vertexBuffers.back().update(vertex);
            selects[i] = true;
          }
        }
        else {
          if(selects[i]) {
            for(uint8_t j = 0; j < 16; j++) {
              vertex[i * 16 + j].color = sf::Color(0, 255, 0, 255);
            }
            screen_->vertexBuffers.back().update(vertex);
            selects[i] = false;
          }
        }
      }
    }
    creators.update(gametime);
  }

  virtual void draw() override {
    screen_->clear();
    screen_->draw();
    creators.draw(*screen_);
    screen_->display();
  }
};