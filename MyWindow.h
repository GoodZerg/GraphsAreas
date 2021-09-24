#pragma once

#include "Function.h"

class MyWindow {
public:
  MyWindow();
  ~MyWindow();
  void render() const;
private:
  sf::RenderWindow* window_ = nullptr;
  sf::View& view_;
  sf::View view__ = {};
  Function* a_ = nullptr;
  Function* a1_ = nullptr;
  Function* a2_ = nullptr;
};

