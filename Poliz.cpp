#include "Poliz.h"

enum class Poliz::SymbolType {
  PLUS,
  MINUS,
  MULTIPLICATION,
  DIVISION,
  DEGREE,
  OPEN_BRACKET,
  CLOSE_BRACKET,
  NUMBER,
  SIN,
  COS,
  LN,
  EXP,
  SQRT
};

enum class Poliz::ActivitiesWithSymbol {
  ADD_WITHOUT_SPACE_TO_ANSWER,
  ADD_WITH_SPACE_TO_ANSWER,
  ADD_TO_DEQUE,
  GET_FROM_DEQUE_TO_OPEN_BRACKET,
  ADD_UNARY
};


FuncMap Poliz::f_map = {
  {"+", [](Bdouble f, Bdouble s) -> Bdouble { return f + s; }},
  {"-", [](Bdouble f, Bdouble s) -> Bdouble { return s - f; }},
  {"*", [](Bdouble f, Bdouble s) -> Bdouble { return s * f; }},
  {"/", [](Bdouble f, Bdouble s) -> Bdouble { return s / f; }},
  {"^", [](Bdouble f, Bdouble s) -> Bdouble { return std::pow(s,f); }},
  {"_", [](Bdouble f, Bdouble s) -> Bdouble { return -f; }},
  {"#", [](Bdouble f, Bdouble s) -> Bdouble { return std::sin(f); }},
  {"$", [](Bdouble f, Bdouble s) -> Bdouble { return std::cos(f); }},
  {"@", [](Bdouble f, Bdouble s) -> Bdouble { return std::log(f); }},
  {"!", [](Bdouble f, Bdouble s) -> Bdouble { return std::exp(f); }},
  {"?", [](Bdouble f, Bdouble s) -> Bdouble { return std::sqrt(f); }}
};


Poliz::Poliz(std::string str) {
  this->base_str_ = str;
  ConverToPoliz(str);
}

void Poliz::ConverToPoliz(std::string str) {
  std::deque<char> main_deque;
  std::string poliz_str;
  char previous_symbol = NULL;

  while (str.find("sin") != std::string::npos) {
    str.replace(str.find("sin"), 3, "#");
  }
  while (str.find("cos") != std::string::npos) {
    str.replace(str.find("cos"), 3, "$");
  }
  while (str.find("ln") != std::string::npos) {
    str.replace(str.find("ln"), 2, "@");
  }
  while (str.find("exp") != std::string::npos) {
    str.replace(str.find("exp"), 3, "!");
  }
  while (str.find("sqrt") != std::string::npos) {
    str.replace(str.find("sqrt"), 4, "?");
  }

  for (char symbol : str) {
    DoAnAction(SelectingAnAction(CheckTypeSymbol(symbol), previous_symbol), 
      main_deque, poliz_str, CheckTypeSymbol(symbol), symbol);
    previous_symbol = symbol;
  }
  main_deque.push_front('(');
  bool flag = true;
  while (!main_deque.empty()) {
    if (main_deque.back() != '(') {
      poliz_str += main_deque.back();
    } else {
      flag = false;
    }
    main_deque.pop_back();
    if (!flag) {
      break;
    }
  }
  this->poliz_ = poliz_str;
}

Bdouble Poliz::GetY(Bdouble x) const {
  std::string poliz = this->poliz_;
  while (poliz.find('x') != std::string::npos) {
    poliz.replace(poliz.find('x'), 1, x < 0 ? std::to_string(std::abs(x)) + "_" :std::to_string(x));
  }
  std::stack <Bdouble> numbers_in_polis;
  bool flag = false;
  std::string tmp = "";
  std::vector<Bdouble> arr;
  for (int64_t element = poliz.size() - 1, in = -1; element >= 0; --element) {
    if ((poliz[element] >= '0' && poliz[element] <= '9') || poliz[element] == '.') {
      tmp += poliz[element];
      flag = true;
      poliz[element] = 'n';
    }
    else {
      if (flag) {
        std::reverse(tmp.begin(), tmp.end());
        arr.push_back(std::stold(tmp));
      }
      flag = false;
      tmp = "";
    }
  }
  if (flag) {
    std::reverse(tmp.begin(), tmp.end());
    arr.push_back(std::stold(tmp));
  }
  flag = false;
  tmp = "";
  int64_t in = arr.size() - 1;
  flag = true;
  for (char element : poliz) {
    if (element != ' ' && element != 'n') {
      flag = true;
      
      Bdouble first = numbers_in_polis.top();
      numbers_in_polis.pop();
      Bdouble second = 0;
      if (element == '+' || element == '-' || element == '*' || element == '/' || element == '^') {
        second = numbers_in_polis.top();
        numbers_in_polis.pop();
      }
      std::string tmp = " ";
      tmp[0] = element;
      numbers_in_polis.push(f_map.at(tmp)(first, second));
      
    }
    else {
      if (element == 'n' && flag) {
        numbers_in_polis.push(arr[in]);
        flag = false;
        --in;
      }
      else {
        if (element != 'n') {
          flag = true;
        }
      }
    }
  }
  return numbers_in_polis.top();
}

std::string Poliz::GetBaseStr() const {
  return base_str_;
}

Poliz::SymbolType Poliz::CheckTypeSymbol(char& symbol) {
  if ((symbol >= '0' && symbol <= '9') || symbol == '.' || symbol == 'x') {
    return SymbolType::NUMBER;
  }
  if (symbol == '+') {
    return SymbolType::PLUS;
  }
  if (symbol == '-') {
    return SymbolType::MINUS;
  }
  if (symbol == '*') {
    return SymbolType::MULTIPLICATION;
  }
  if (symbol == '/') {
    return SymbolType::DIVISION;
  }
  if (symbol == '^') {
    return SymbolType::DEGREE;
  }
  if (symbol == '(') {
    return SymbolType::OPEN_BRACKET;
  }
  if (symbol == ')') {
    return SymbolType::CLOSE_BRACKET;
  }
  if (symbol == '#') {
    return SymbolType::SIN;
  }
  if (symbol == '$') {
    return SymbolType::COS;
  }
  if (symbol == '@') {
    return SymbolType::LN;
  }
  if (symbol == '!') {
    return SymbolType::EXP;
  }
  if (symbol == '?') {
    return SymbolType::SQRT;
  }
}

Poliz::ActivitiesWithSymbol Poliz::SelectingAnAction(SymbolType symbol, char& previous_symbol) {
  if (previous_symbol == NULL) {
    if (symbol == SymbolType::NUMBER) {
      return ActivitiesWithSymbol::ADD_WITHOUT_SPACE_TO_ANSWER;
    }
    if (symbol == SymbolType::MINUS || symbol == SymbolType::SIN || 
      symbol == SymbolType::COS || symbol == SymbolType::LN ||
      symbol == SymbolType::EXP || symbol == SymbolType::SQRT) {
      return ActivitiesWithSymbol::ADD_UNARY;
    }
    if (symbol == SymbolType::OPEN_BRACKET) {
      return ActivitiesWithSymbol::ADD_TO_DEQUE;
    }
  } else {
    SymbolType previous_symbol_type = CheckTypeSymbol(previous_symbol);
    if (symbol == SymbolType::NUMBER) {
      if (previous_symbol_type == SymbolType::NUMBER) {
        return ActivitiesWithSymbol::ADD_WITHOUT_SPACE_TO_ANSWER;
      } else {
        return ActivitiesWithSymbol::ADD_WITH_SPACE_TO_ANSWER;
      }
    }
    if (symbol == SymbolType::PLUS) {
      return ActivitiesWithSymbol::ADD_TO_DEQUE;
    }
    if (symbol == SymbolType::MINUS) {
      if (previous_symbol_type != SymbolType::NUMBER && previous_symbol_type != SymbolType::CLOSE_BRACKET) {
        return ActivitiesWithSymbol::ADD_UNARY;
      } else {
        return ActivitiesWithSymbol::ADD_TO_DEQUE;
      }
    }
    if (symbol == SymbolType::SIN || symbol == SymbolType::COS || symbol == SymbolType::LN || 
      symbol == SymbolType::EXP || symbol == SymbolType::SQRT) {
      return ActivitiesWithSymbol::ADD_UNARY;
    }
    if (symbol == SymbolType::MULTIPLICATION || symbol == SymbolType::DIVISION || symbol == SymbolType::DEGREE || symbol == SymbolType::OPEN_BRACKET) {
      return ActivitiesWithSymbol::ADD_TO_DEQUE;
    }
    if (symbol == SymbolType::CLOSE_BRACKET) {
      return ActivitiesWithSymbol::GET_FROM_DEQUE_TO_OPEN_BRACKET;
    }
  }
}

void Poliz::DoAnAction(ActivitiesWithSymbol activity, std::deque<char>& main_deque, 
  std::string& polis_string, SymbolType symbol_type, char& symbol) {
  if (activity == ActivitiesWithSymbol::ADD_WITHOUT_SPACE_TO_ANSWER) {
    polis_string += symbol;
    return;
  }
  if (activity == ActivitiesWithSymbol::ADD_WITH_SPACE_TO_ANSWER) {
    polis_string += " ";
    polis_string += symbol;
    return;
  }
  if (activity == ActivitiesWithSymbol::ADD_UNARY) {
    if (symbol_type == SymbolType::MINUS) {
      main_deque.push_back('_');
      return;
    }
    if (symbol_type == SymbolType::SIN) {
      main_deque.push_back('#');
      return;
    }
    if (symbol_type == SymbolType::COS) {
      main_deque.push_back('$');
      return;
    }
    if (symbol_type == SymbolType::LN) {
      main_deque.push_back('@');
      return;
    }
    if (symbol_type == SymbolType::EXP) {
      main_deque.push_back('!');
      return;
    }
    if (symbol_type == SymbolType::SQRT) {
      main_deque.push_back('?');
      return;
    }

  }
  if (activity == ActivitiesWithSymbol::ADD_TO_DEQUE) {
    if (symbol_type == SymbolType::OPEN_BRACKET) {
      main_deque.push_back('(');
      return;
    }
    if (symbol_type == SymbolType::PLUS || symbol_type == SymbolType::MINUS) {
      while (!main_deque.empty()) {
        if (main_deque.back() == '*' || main_deque.back() == '/' || main_deque.back() == '^' ||
          main_deque.back() == '#' || main_deque.back() == '_' || main_deque.back() == '+' || 
          main_deque.back() == '-' || main_deque.back() == '$' || main_deque.back() == '@' ||
          main_deque.back() == '!' || main_deque.back() == '?') {
          polis_string += main_deque.back();
        }
        else {
          main_deque.push_back(symbol_type == SymbolType::PLUS ? '+' : '-');
          break;
        }
        main_deque.pop_back();
      }
      if (main_deque.empty()) {
        main_deque.push_back(symbol_type == SymbolType::PLUS ? '+' : '-');
      }
    }
    if (symbol_type == SymbolType::MULTIPLICATION || symbol_type == SymbolType::DIVISION) {
      while (!main_deque.empty()) {
        if (main_deque.back() == '^' || main_deque.back() == '_' || main_deque.back() == '#' || 
          main_deque.back() == '*' || main_deque.back() == '/' || main_deque.back() == '$' ||
          main_deque.back() == '@' || main_deque.back() == '!' || main_deque.back() == '?') {
          polis_string += main_deque.back();
        }
        else {
          main_deque.push_back(symbol_type == SymbolType::MULTIPLICATION ? '*' : '/');
          break;
        }
        main_deque.pop_back();
      }
      if (main_deque.empty()) {
        main_deque.push_back(symbol_type == SymbolType::MULTIPLICATION ? '*' : '/');
      }
    }
    if (symbol_type == SymbolType::DEGREE) {
      while (!main_deque.empty()) {
        if (main_deque.back() == '_' || main_deque.back() == '#' || main_deque.back() == '$' ||
          main_deque.back() == '@' || main_deque.back() == '!' || main_deque.back() == '?') {
          polis_string += main_deque.back();
        }
        else {
          main_deque.push_back('^');
          break;
        }
        main_deque.pop_back();
      }
      if (main_deque.empty()) {
        main_deque.push_back('^');
      }
    }
  }
  if (activity == ActivitiesWithSymbol::GET_FROM_DEQUE_TO_OPEN_BRACKET) {
    bool flag = true;
    while (!main_deque.empty()) {
      if (main_deque.back() != '(') {
        polis_string += main_deque.back();
      } else {
        flag = false;
      }
      main_deque.pop_back();
      if (!flag) {
        break;
      }
    }
    return;
  }
}
