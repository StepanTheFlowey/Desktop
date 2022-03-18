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
public:
  sf::RenderWindow window;
  sf::Event event;

  Screen():window(), event() {}

  void init() {
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    videoMode.height--;

    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 0;

    window.create(videoMode, "", sf::Style::None, contextSettings);
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    //Window transperency magic
    SetLastError(0);
    LONG result = SetWindowLongW(window.getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
    if(result == 0) {
      std::wcout << L"Error!" << std::endl;
      std::wcout << L"SetWindowLongW(GWL_STYLE) output is zero!" << std::endl;
      lastError();
      //_wsystem(L"pause");
      //exit(0);
    }

    //result = SetWindowLongW(window.getSystemHandle(), GWL_EXSTYLE,  WS_EX_APPWINDOW);
    //if(result == 0) {
      //std::wcout << L"Error!" << std::endl;
      //std::wcout << L"SetWindowLongW(GWL_EXSTYLE) output is zero!" << std::endl;
      //lastError();
      //_wsystem(L"pause");
      //exit(0);
    //}

    HRESULT hr = S_OK;

    //DWMNCRENDERINGPOLICY ncrp = DWMNCRP_ENABLED;

    //hr = DwmSetWindowAttribute(window.getSystemHandle(), DWMWA_NCRENDERING_POLICY, &ncrp, sizeof(ncrp));
    //if(FAILED(hr)) {
    //  std::wcout << L"Error!" << std::endl;
    //  std::wcout << L"DwmSetWindowAttribute output:\n0x" << std::hex << hr << std::endl;
    //  _wsystem(L"pause");
    //  exit(0);
    //}

    //RECT extendedFrameBounds {0,0,0,0};
    //hr = DwmGetWindowAttribute(window.getSystemHandle(), DWMWA_EXTENDED_FRAME_BOUNDS, &extendedFrameBounds, sizeof(extendedFrameBounds));

    BOOL compEn = false;
    hr = S_OK;
    hr = DwmIsCompositionEnabled(&compEn);
    if(FAILED(hr)) {
      std::wcout << L"Error!" << std::endl;
      std::wcout << L"DwmIsCompositionEnabled output:\n0x" << std::hex << hr << std::endl;
      _wsystem(L"pause");
      exit(0);
    }
    if(!compEn) {
      std::wcout << L"Error!" << std::endl;
      std::wcout << L"Composition disabled!" << std::endl;
      _wsystem(L"pause");
      exit(0);
    }

    MARGINS margins = {-1};
    hr = S_OK;
    hr = DwmExtendFrameIntoClientArea(window.getSystemHandle(), &margins);
    if(FAILED(hr)) {
      std::wcout << L"Error!" << std::endl;
      std::wcout << L"DwmExtendFrameIntoClientArea output:\n0x" << std::hex << hr << std::endl;
      _wsystem(L"pause");
      exit(0);
    }
  }

  void ignoreEvents() {
    while(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window.close();
        exit(0);
      }
    };
  }

  bool precessEvent() {
    return window.pollEvent(event);
  }

  int play(Scene *scene);

  friend Creator;
private:
  void lastError() {
    std::wcout << L"GetLastError(): 0x" << std::hex << GetLastError() << std::endl;
  }
};