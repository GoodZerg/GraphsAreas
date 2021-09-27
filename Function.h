#pragma once

#include "Poliz.h"

class Function {
public:
  Function(sf::RenderWindow& window, std::string str);
  void render() const;
  Bdouble findValue(Bdouble x) const;
private:
  Poliz* poliz_ = nullptr;
  sf::RenderWindow* context_ = nullptr;
  sf::Vertex line[4000];
};
