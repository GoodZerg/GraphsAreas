#include "MyWindow.h"

Bdouble random_double_range(Bdouble const range_min, Bdouble const range_max) {
  static unsigned long long const mant_mask53(9007199254740991);
  static double const i_to_d53(1.0 / 9007199254740992.0);
  unsigned long long const r((unsigned long long(rand()) | (unsigned long long(rand()) << 15) | 
    (unsigned long long(rand()) << 30) | (unsigned long long(rand()) << 45)) & mant_mask53);
  return range_min + i_to_d53 * Bdouble(r) * (range_max - range_min);
}

MyWindow::MyWindow() : view_(view__){
  window_ = new sf::RenderWindow(C_window_size, "My window");
  view_ = window_->getDefaultView();
  window_->setView(view_);
  view_.move(-view_.getSize().x / 2, -view_.getSize().y / 2);

  a_ = new Function(*window_, "ln(x)");
  a1_ = new Function(*window_, "-2*x+14");
  a2_ = new Function(*window_, "1/(2-x)+6");

  x01_ = FindRoots(a_, a1_);
  x02_ = FindRoots(a_, a2_);
  x12_ = FindRoots(a1_, a2_);

  std::cout << "points: " << x01_ << " " << x02_ << " " << x12_ << "\n";

  square0_ = FindIntegral(a_, std::min(x01_, x02_), std::max(x01_, x02_));
  square1_ = FindIntegral(a1_, std::min(x01_, x12_), std::max(x01_, x12_));
  square2_ = FindIntegral(a2_, std::min(x02_, x12_), std::max(x02_, x12_));

  std::cout << "areas: " << square0_ << " " << square1_ << " " << square2_ << "\n";

  if (std::abs(x01_ - x02_) >= std::abs(x01_ - x12_) &&
    std::abs(x01_ - x02_) >= std::abs(x02_ - x12_)) {
    square_integral_ = std::abs(square0_ - square1_ - square2_);
  }
  if (std::abs(x01_ - x12_) >= std::abs(x01_ - x02_) &&
    std::abs(x01_ - x12_) >= std::abs(x02_ - x12_)) {
    square_integral_ = std::abs(square1_ - square0_ - square2_);
  }
  if (std::abs(x02_ - x12_) >= std::abs(x01_ - x12_) &&
    std::abs(x02_ - x12_) >= std::abs(x01_ - x02_)) {
    square_integral_ = std::abs(square2_ - square1_ - square0_);
  }

  std::cout << "integral answer: " << square_integral_ << "\n";

  x2_ = std::max(x01_, std::max( x02_, x12_));
  x1_ = std::min(x01_, std::min(x02_, x12_));
  y2_ = std::max(a_->findValue(x01_), std::max(a_->findValue(x02_), a1_->findValue(x12_)));
  y1_ = std::min(a_->findValue(x01_), std::min(a_->findValue(x02_), a1_->findValue(x12_)));

  //std::cout << x1_ << " " << x2_ << " " << y1_ << " " << y2_ << " " << "\n";

  sign1_ = a1_->findValue(x12_) >  a_->findValue(x12_);
  sign2_ = a_->findValue(x02_)  > a1_->findValue(x02_);
  sign3_ = a1_->findValue(x01_) > a2_->findValue(x01_);

  //std::cout << sign1 << " " << sign2 << " " << sign3 << "\n";

  big_square_ = std::abs(x2_ - x1_) * std::abs(y2_ - y1_);

  rng_ans_square_ = FindRngSquare();

  std::cout << "rng answer: " << rng_ans_square_ << "\n";

}


Bdouble MyWindow::FindRngSquare() {
  size_t hit = 0;
  size_t times = 300000;
  for (size_t i = 0; i < times; i++) {
    Bdouble r_x = random_double_range(x1_, x2_);
    Bdouble r_y = random_double_range(y1_, y2_);


    if (sign1_) {
      if (r_y < a_->findValue(r_x)) {
        continue;
      }
    } else {
      if (r_y > a_->findValue(r_x)) {
        continue;
      }
    }

    if (sign2_) {
      if (r_y < a1_->findValue(r_x)) {
        continue;
      }
    } else {
      if (r_y > a1_->findValue(r_x)) {
        continue;
      }
    }

    if (sign3_) {
      if (r_y < a2_->findValue(r_x)) {
        continue;
      }
    } else {
      if (r_y > a2_->findValue(r_x)) {
        continue;
      }
    }

    hit++;

  }

  return big_square_ * hit / static_cast<Bdouble>(times);
}

Bdouble MyWindow::FindIntegral(Function* f, Bdouble x0, Bdouble x1) {
  Bdouble eps = 1e-7;
  Bdouble square_prev = 1, square_current = 0;
  size_t steps = 10;
  while (std::abs(square_prev - square_current) > eps && steps <= 10000000) {
    square_prev = square_current;
    square_current = 0;
    for (size_t i = 0; i < steps; ++i) {
      square_current += std::abs(((x1 - x0) / steps) * 
        f->findValue(x0 + ((x1 - x0) / steps) * i + ((x1 - x0) / steps) / 2));
    }
    steps <<= 1;
  }
  return square_current;
}

Bdouble MyWindow::FindRoots(Function* f1, Function* f2) {
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
