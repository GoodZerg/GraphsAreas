#include "MyWindow.h"

MyWindow::MyWindow() : view_(view__){
  window_ = new sf::RenderWindow(C_window_size, "My window");
  view_ = window_->getDefaultView();
  window_->setView(view_);
  view_.move(-view_.getSize().x / 2, -view_.getSize().y / 2);
  a_ =  new Function(*window_, "(x+3)*(x-5)*(x-7)");
  a1_ = new Function(*window_, "sin(x)");
  a2_ = new Function(*window_, "ln(x)");
}

MyWindow::~MyWindow() {
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
      sf::RectangleShape line_with_thickness(sf::Vector2f(C_grid_lenght, i == C_grid_lines / 2 ? 15.f : 5.f));
      line_with_thickness.rotate(90.f);
      line_with_thickness.setFillColor(C_grid_color);
      line_with_thickness.move(-1 * C_grid_lines / 2 * C_grid_step + i * C_grid_step + line_with_thickness.getSize().y / 2, -1 * C_grid_lines / 2 * C_grid_step);
      window_->draw(line_with_thickness);

      sf::RectangleShape line_with_thickness2(sf::Vector2f(C_grid_lenght, i == C_grid_lines / 2 ? 15.f : 5.f));
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
