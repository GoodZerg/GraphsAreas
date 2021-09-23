#include "Function.h"

Function::Function(sf::RenderWindow& window, std::string str) {
  this->poliz_ = new Poliz(str);
  this->context_ = &window;
}

void Function::render() const{
}

Bdouble Function::findValue(Bdouble x) const {
  return poliz_->GetY(x);
}
