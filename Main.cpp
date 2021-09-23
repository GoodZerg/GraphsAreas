#include "Header.h"



int main() {
  sf::RenderWindow window(C_window_size, "My window");
  sf::View view = window.getDefaultView();
  window.setView(view);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right) {
          view.move(+view.getSize().x / 20, 0.f);
          window.setView(view);
        }
        if (event.key.code == sf::Keyboard::Left) {
          view.move(-view.getSize().x / 20, 0.f);
          window.setView(view);
        }
        if (event.key.code == sf::Keyboard::Up) {
          view.move(0.f, -view.getSize().y / 20);
          window.setView(view);
        }
        if (event.key.code == sf::Keyboard::Down) {
          view.move(0.f, +view.getSize().y / 20);
          window.setView(view);
        }
      }
      if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
          view.zoom(0.9f);
          window.setView(view);
        }
        if (event.mouseWheelScroll.delta < 0) {
          view.zoom(1.1f);
          window.setView(view);
        }
      }
    }

    window.clear(C_back_color);

    for (int i = 0; i < C_grid_lines; ++i) {
      sf::RectangleShape line_with_thickness(sf::Vector2f(C_grid_lenght, 5.f));
      line_with_thickness.rotate(90.f);
      line_with_thickness.setFillColor(C_grid_color);
      line_with_thickness.move(-1 * C_grid_lines/2 * C_grid_step + i * C_grid_step, -1* C_grid_lines/2 * C_grid_step);
      window.draw(line_with_thickness);

      sf::RectangleShape line_with_thickness2(sf::Vector2f(C_grid_lenght, 5.f));
      line_with_thickness2.rotate(0.f);
      line_with_thickness2.setFillColor(C_grid_color);
      line_with_thickness2.move(-1* C_grid_lines/2 * C_grid_step, -1* C_grid_lines/2 * C_grid_step + i * C_grid_step);
      window.draw(line_with_thickness2);
    }

		window.display();
  }

  return 0;
}