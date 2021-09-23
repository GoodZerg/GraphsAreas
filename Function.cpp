#include "Function.h"

const Bdouble max_y = 66666666;
const Bdouble min_y = -66666666;

Function::Function(sf::RenderWindow& window, std::string str) {
  this->poliz_ = new Poliz(str);
  this->context_ = &window;


  for (Bdouble i = -10000; i < 10000; i += 10) {
    Bdouble y = -findValue(i / 100) * 100;
    if(y > 60000) {
      y = max_y;
    }
    if (y < -60000) {
      y = min_y;
    }
    line[static_cast<int>((i + 10000)/10)] = sf::Vector2f(i, y);
    line[static_cast<int>((i + 10000)/10)].color = sf::Color::Black;
  }
  
}

void Function::render() const {
  sf::VertexArray graph(sf::LinesStrip, 2);
  for (size_t i = 1; i < 2000; i+=1) {
    if (line[i - 1].position.y == min_y) continue;
    if (line[i - 1].position.y == max_y) break;
    Bdouble rr =  line[i].position.y - line[i - 1].position.y;
    if (rr < -999999) continue;
    graph[0] = line[i - 1];
    graph[1] = line[i];
    context_->draw(graph);
  }
}

Bdouble Function::findValue(Bdouble x) const {
  return poliz_->GetY(x);
}
