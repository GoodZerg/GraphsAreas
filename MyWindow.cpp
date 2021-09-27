#include "MyWindow.h"

MyWindow::MyWindow() : view_(view__){
  window_ = new sf::RenderWindow(C_window_size, "My window");
  view_ = window_->getDefaultView();
  window_->setView(view_);
  view_.move(-view_.getSize().x / 2, -view_.getSize().y / 2);
  a_ = new Function(*window_, "ln(x)");
  a1_ = new Function(*window_, "-2*x+14");
  a2_ = new Function(*window_, "1/(2-x)+6");
  x01_ = findInsert(a_, a1_);
  x02_ = findInsert(a_, a2_);
  x12_ = findInsert(a1_, a2_);
  std::cout << x01_ << " " << x02_ << " " << x12_ << std::endl;
}

Bdouble MyWindow::findInsert(Function* f1, Function* f2) {
  Bdouble left = -100, right = 100;
  Bdouble eps = 1e-2;
  Bdouble point = 0;
  for (; eps >= 1e-6; eps /= 10) {
    for (Bdouble i = right; i >= left; i -= eps) {
      if (std::abs(f1->findValue(i) - f2->findValue(i)) <= eps * 10) {
        point = i;
        break;
      }
    }
    left = point - eps * 10;
    right = point + eps * 10;
  }
  return point;
}

MyWindow::~MyWindow() {
  delete window_;
  delete a_;
  delete a1_;
  delete a2_;
}

void MyWindow::render() const {
  while (window_->isOpen()) {
    sf::Event event;
    while (window_->pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window_->close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right) {
          view_.move(+view_.getSize().x / 20, 0.f);
          window_->setView(view_);
        }
        if (event.key.code == sf::Keyboard::Left) {
          view_.move(-view_.getSize().x / 20, 0.f);
          window_->setView(view_);
        }
        if (event.key.code == sf::Keyboard::Up) {
          view_.move(0.f, -view_.getSize().y / 20);
          window_->setView(view_);
        }
        if (event.key.code == sf::Keyboard::Down) {
          view_.move(0.f, +view_.getSize().y / 20);
          window_->setView(view_);
        }
      }
      if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
          view_.zoom(0.9f);
          window_->setView(view_);
        }
        if (event.mouseWheelScroll.delta < 0) {
          view_.zoom(1.1f);
          window_->setView(view_);
        }
      }
    }

    window_->clear(C_back_color);


    for (int i = 0; i < C_grid_lines; ++i) {
      sf::RectangleShape line_with_thickness(sf::Vector2f(C_grid_lenght, i == C_grid_lines / 2 ? 5.f : 2.f));
      line_with_thickness.rotate(90.f);
      line_with_thickness.setFillColor(C_grid_color);
      line_with_thickness.move(-1 * C_grid_lines / 2 * C_grid_step + i * C_grid_step + line_with_thickness.getSize().y / 2, -1 * C_grid_lines / 2 * C_grid_step);
      window_->draw(line_with_thickness);

      sf::RectangleShape line_with_thickness2(sf::Vector2f(C_grid_lenght, i == C_grid_lines / 2 ? 5.f : 2.f));
      line_with_thickness2.rotate(0.f);
      line_with_thickness2.setFillColor(C_grid_color);
      line_with_thickness2.move(-1 * C_grid_lines / 2 * C_grid_step, -1 * C_grid_lines / 2 * C_grid_step + i * C_grid_step - line_with_thickness.getSize().y / 2);
      window_->draw(line_with_thickness2);
    }

    a_->render();
    a1_->render();
    a2_->render();
    window_->display();
  }
}
