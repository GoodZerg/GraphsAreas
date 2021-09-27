#pragma once

#include "Function.h"

class MyWindow {
public:
  MyWindow();
  ~MyWindow();
  void render() const;
private:
  Bdouble findInsert(Function* f1, Function* f2);

  sf::RenderWindow* window_ = nullptr;
  sf::View& view_;
  sf::View view__ = {};

  Bdouble x01_, x02_, x12_;

  Function* a_ = nullptr;
  Function* a1_ = nullptr;
  Function* a2_ = nullptr;
};

