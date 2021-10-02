//Math
#define NOMINMAX
#include <cmath>

//Containers
#include <unordered_map>
#include <vector>

//IO
#include <iostream>
#include <conio.h>
#include <fstream>

//WinAPI
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Dwmapi.h>

//SFML 
#include <SFML\Graphics.hpp>

#include "types.h"
#include "creatorArray.hpp"
#include "screen.hpp"
#include "scene.hpp"

#include "sceneStart.hpp"
#include "sceneMenu.hpp"

bool warning() {
  return MessageBoxW(NULL, L"This application is dangerous\n\nDo you want to continue?", L"Warning", MB_YESNO | MB_ICONWARNING) == IDYES;
}

void load() {
  std::wifstream file(L"file0.txt");

  file.close();
}

void save() {
  std::wofstream file(L"file0.txt");

  file.close();
}

template <class S> void playScene(Screen &screen) {
  Scene *scene = nullptr;
  scene = new S;
  screen.play(scene);
  delete scene;
}

int main() {
  srand(static_cast<unsigned int>(time(0)));
  if(!warning()) {
    return 0;
  }

  sf::ContextSettings contextSettings;
  contextSettings.antialiasingLevel = 8;

  Screen screen(contextSettings);

  playScene<SceneStart>(screen);
#ifndef DEBUG
  FreeConsole();
#endif //DEBUG
  playScene<SceneMenu>(screen);
}