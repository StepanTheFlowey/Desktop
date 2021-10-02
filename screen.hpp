#pragma once
#include "types.h"
#include "creatorArray.hpp"
#include "creator.hpp"

//Containers
#include <vector>

//IO
#include <fstream>

//WinAPI
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Dwmapi.h>

//SFML
#include <SFML\Graphics.hpp>

class Creator;
class Scene;

class Screen {
  sf::RenderWindow window_;
public:
  sf::Event event;
  sf::Color clearColor;
  std::vector<sf::VertexBuffer> vertexBuffers;
  std::vector<sf::Text> texts;
  std::vector<sf::Font> fonts;

  Screen() {
    throw;
  }

  Screen(sf::ContextSettings contextSettings):window_(sf::VideoMode::getDesktopMode(), "", sf::Style::None, contextSettings), event() {
    window_.setVerticalSyncEnabled(true);

    //Window transperency magic
    LONG result = SetWindowLongW(window_.getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
    if(result == 0) {
      std::wcout << L"Error!" << std::endl;
      std::wcout << L"SetWindowLongW output is zero!" << std::endl;
      _wsystem(L"pause");
    }

    HRESULT hr = S_OK;
    BOOL compEn = false;
    hr = DwmIsCompositionEnabled(&compEn);
    if(FAILED(hr)) {
      std::wcout << L"Error!" << std::endl;
      std::wcout << L"DwmIsCompositionEnabled output:\n0x" << std::hex << hr << std::endl;
      _wsystem(L"pause");
    }
    if(!compEn) {
      std::wcout << L"Error!" << std::endl;
      std::wcout << L"Composition disabled!" << std::endl;
      _wsystem(L"pause");
    }

    MARGINS margins = {-1};
    hr = S_OK;
    hr = DwmExtendFrameIntoClientArea(window_.getSystemHandle(), &margins);
    if(FAILED(hr)) {
      std::wcout << L"Error!" << std::endl;
      std::wcout << L"DwmExtendFrameIntoClientArea output:\n0x" << std::hex << hr << std::endl;
      _wsystem(L"pause");
    }
  }

  void ignoreEvents() {
    while(window_.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window_.close();
        exit(0);
      }
    };
  }

  bool precessEvent() {
    return window_.pollEvent(event);
  }

  void draw() {
    for(auto &i : vertexBuffers) {
      window_.draw(i);
    }
    for(auto &i : texts) {
      window_.draw(i);
    }
  }

  void clear() {
    window_.clear(clearColor);
  }

  void display() {
    window_.display();
  }

  void play(Scene *scene);

  friend Creator;
  friend Scene;
};