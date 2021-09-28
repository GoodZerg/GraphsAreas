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
  Bdouble FindRngSquare();

  sf::RenderWindow* window_ = nullptr;
  sf::View& view_;
  sf::View view__ = {};

  Bdouble square0_, square1_, square2_;
  Bdouble square_integral_;

  Bdouble x01_, x02_, x12_;

  Bdouble x1_, x2_, y1_, y2_;

  bool sign1, sign2, sign3;

  Bdouble big_square_;
  Bdouble rng_ans_square_;

  Function* a_ = nullptr;
  Function* a1_ = nullptr;
  Function* a2_ = nullptr;
};

