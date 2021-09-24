#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
#include <stack>
#include <limits.h>
#include <math.h>
#include <deque>
#include <cmath>
#include <map>

const double C_X = DBL_MAX;
const sf::VideoMode C_window_size = sf::VideoMode(800, 600);
const sf::Color C_back_color = sf::Color(180, 180, 180, 0);
const int C_grid_step = 100;
const int C_grid_lines = 1000;
const int C_grid_lenght = C_grid_step * C_grid_lines;
const sf::Color C_grid_color = sf::Color(100, 100, 100);


typedef  long double Bdouble;
typedef  std::function<Bdouble(Bdouble, Bdouble)> Func;
typedef  std::map<std::string, std::function<Bdouble(Bdouble, Bdouble)>> FuncMap;
