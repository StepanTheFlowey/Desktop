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

  bool close = false;
  bool open = false;
  uint8_t openStage = 0;
  uint8_t openCounter = 0;
  gametime_t timeElapsed = 0;

  sf::RectangleShape shadeRect;
  sf::VertexBuffer vbo;
  sf::Vertex vertex[80];
  sf::FloatRect rects[4];
  bool selects[4];
  uint8_t selected = 0;

  sf::Vector2i movingMousePos;
  sf::Vector2i movingMouseOffset;
  sf::Vector2i movingMouseTarget;
  CreatorArray::ID_t movingMouseCreator = NULL;

  sf::Color backgroundColor;

  sf::Clock clock;
  CreatorArray creators;
  gametime_t gametime = 0;

  sf::Texture tileset;
public:
  SceneMenu() {
    vbo.setPrimitiveType(sf::Quads);
    vbo.setUsage(sf::VertexBuffer::Stream);
    vbo.create(80);
    backgroundColor = sf::Color(0, 0, 0, 0);
    for(uint8_t i = 0; i < 64; i++) {
      vertex[i].color = sf::Color(0, 255, 0, 255);
    }
    for(uint8_t i = 64; i < 80; i++) {
      vertex[i].color = sf::Color(255, 255, 255, 255);
    }
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
    for(uint8_t i = 0; i < 4; i++) {
      index = 64 + i * 4;
      vertex[index + 0].position = sf::Vector2f(rects[i].left + 5, rects[i].top + 5);
      vertex[index + 1].position = sf::Vector2f(rects[i].left + 5, rects[i].top + rects[i].height - 5);
      vertex[index + 2].position = sf::Vector2f(rects[i].left + rects[i].width - 5, rects[i].top + rects[i].height - 5);
      vertex[index + 3].position = sf::Vector2f(rects[i].left + rects[i].width - 5, rects[0].top + 5);

      vertex[index + 0].texCoords = sf::Vector2f(0, 0);
      vertex[index + 1].texCoords = sf::Vector2f(0, 16);
      vertex[index + 2].texCoords = sf::Vector2f(16, 16);
      vertex[index + 3].texCoords = sf::Vector2f(16, 0);
    }
    shadeRect.setPosition(0.0F, 0.0F);
    shadeRect.setSize(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
    shadeRect.setFillColor(sf::Color::Transparent);
  }

  virtual int play(Screen *screen) override {
    screen_ = screen;

    tileset.loadFromFile("assets\\textures\\menu.png");

    clock.restart();
    while(work_) {
      gametime = clock.restart().asMilliseconds();
      screen_->ignoreEvents();
      update();
      draw();
    }
    return selected + 1;
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
            creators.changeWidth(creators.newCreator(getRandomCreatorBeginPos(), sf::Vector2i(rects[openStage].left, rects[openStage].top), -1), 10, 0, 1, 50, true);
            break;
          }
          case 1:
          {
            creators.changeWidth(creators.newCreator(getRandomCreatorBeginPos(), sf::Vector2i(rects[openStage].left + rects[openStage].width, rects[openStage].top), -1), 10, 0, 1, 50, true);
            vbo.update(vertex + index, 4, index + 0);
            break;
          }
          case 3:
          {
            creators.changeWidth(creators.newCreator(getRandomCreatorBeginPos(), sf::Vector2i(rects[openStage].left + rects[openStage].width, rects[openStage].top + rects[openStage].height), -1), 10, 0, 1, 50, true);
            vbo.update(vertex + index + 4, 4, index + 4);
            break;
          }
          case 4:
          {
            creators.changeWidth(creators.newCreator(getRandomCreatorBeginPos(), sf::Vector2i(rects[openStage].left, rects[openStage].top + rects[openStage].height), -1), 10, 0, 1, 50, true);
            vbo.update(vertex + index + 8, 4, index + 8);
            break;
          }
          case 5:
          {
            creators.changeWidth(creators.newCreator(getRandomCreatorBeginPos(), sf::Vector2i(rects[openStage].left, rects[openStage].top), -1), 10, 0, 1, 50, true);
            vbo.update(vertex + index + 12, 4, index + 12);
            openStage++;
            openCounter = UINT8_MAX;
            if(openStage == 4) {
              vbo.update(vertex);
              open = true;
            }
            break;
          }
        }
        openCounter++;
      }
    }
    else if(!close) {
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
        backgroundColor = sf::Color(0, 0, 0, baValue);
      }
      const sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition());
      for(uint8_t i = 0; i < 4; i++) {
        if(rects[i].contains(mousePos)) {
          if(!selects[i]) {
            for(uint8_t j = 0; j < 16; j++) {
              vertex[i * 16 + j].color = sf::Color(255, 255, 255, 255);
            }
            vbo.update(vertex);
            selects[i] = true;
          }
        }
        else {
          if(selects[i]) {
            for(uint8_t j = 0; j < 16; j++) {
              vertex[i * 16 + j].color = sf::Color(0, 255, 0, 255);
            }
            vbo.update(vertex);
            selects[i] = false;
          }
        }
      }
      if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && (selects[0] || selects[1] || selects[2] || selects[3])) {
        close = true;
        openStage = 0;
        openCounter = 0;
        for(uint8_t i = 0; i < 4; i++) {
          if(selects[i]) {
            selected = i;
            break;
          }
        }
      }
    }
    else {
      switch(openStage) {
        case 0:
        {
          openCounter++;
          if(openCounter == 50) {
            openCounter = 0;
            openStage++;
          }
          uint8_t index = selected * 16;
          vertex[index + 0].position.y--;
          vertex[index + 1].position.y--;
          vertex[index + 2].position.y--;
          vertex[index + 3].position.y--;
          vertex[index + 4].position.x++;
          vertex[index + 5].position.x++;
          vertex[index + 6].position.x++;
          vertex[index + 7].position.x++;
          vertex[index + 8].position.y++;
          vertex[index + 9].position.y++;
          vertex[index + 10].position.y++;
          vertex[index + 11].position.y++;
          vertex[index + 12].position.x--;
          vertex[index + 13].position.x--;
          vertex[index + 14].position.x--;
          vertex[index + 15].position.x--;
          vbo.update(vertex + index, 16, index);
          break;
        }
        case 1:
        {
          movingMousePos = sf::Mouse::getPosition();
          movingMouseTarget.x = sf::VideoMode::getDesktopMode().width / 2;
          movingMouseTarget.y = sf::VideoMode::getDesktopMode().height / 3;
          movingMouseCreator = creators.newCreator(getRandomCreatorBeginPos<int>(), movingMousePos + sf::Vector2i(10, 10));
          creators.changeWidth(movingMouseCreator, 0, 10, 1, 100);
          openStage++;
          break;
        }
        case 2:
        {
          movingMouseOffset.x = 0;
          movingMouseOffset.y = 0;

          if(movingMousePos.x < movingMouseTarget.x) {
            int16_t sub = movingMouseTarget.x - movingMousePos.x;
            if(sub < 3) {
              movingMouseOffset.x = sub;
            }
            else {
              movingMouseOffset.x = 3;
            }
          }

          if(movingMousePos.y < movingMouseTarget.y) {
            int16_t sub = movingMouseTarget.y - movingMousePos.y;
            if(sub < 3) {
              movingMouseOffset.y = sub;
            }
            else {
              movingMouseOffset.y = 3;
            }
          }

          if(movingMousePos.x > movingMouseTarget.x) {
            movingMouseOffset.x = -3;
          }

          if(movingMousePos.y > movingMouseTarget.y) {
            movingMouseOffset.y = -3;
          }

          movingMousePos += movingMouseOffset;
          sf::Mouse::setPosition(movingMousePos);
          creators.changeEndPos(movingMouseCreator, movingMousePos + sf::Vector2i(10, 10));

          if(movingMousePos == movingMouseTarget) {
            openStage++;
          }
          break;
        }
        case 3:
        {
          openCounter++;
          if(openCounter == UINT8_MAX) {
            work_ = false;
          }
          shadeRect.setFillColor(sf::Color(openCounter, openCounter, openCounter, openCounter));
          sf::Mouse::setPosition(movingMouseTarget);
          break;
        }
      }
    }
    creators.update(gametime);
  }

  virtual void draw() override {
    screen_->window.clear(backgroundColor);
    screen_->window.draw(vbo, 0, 64);
    screen_->window.draw(vbo, 64, 4, &tileset);
    creators.draw(*screen_);
    screen_->window.draw(shadeRect);
    screen_->window.display();
  }
};