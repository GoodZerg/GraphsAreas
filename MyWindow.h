#pragma once

#include "Function.h"

class MyWindow {
public:
  MyWindow();
  ~MyWindow();
  void render() const;

private:
  Bdouble FindRoots(Function* f1, Function* f2);
  Bdouble FindIntegral(Function* f, Bdouble x0, Bdouble x1);


  sf::RenderWindow* window_ = nullptr;
  sf::View& view_;
  sf::View view__ = {};

  Bdouble square0_, square1_, square2_;
  Bdouble square_integral_;

  Bdouble x01_, x02_, x12_;

  Function* a_ = nullptr;
  Function* a1_ = nullptr;
  Function* a2_ = nullptr;
};

