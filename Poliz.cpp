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
  SIN
};

enum class Poliz::ActivitiesWithSymbol {
  ADD_WITHOUT_SPACE_TO_ANSWER,
  ADD_WITH_SPACE_TO_ANSWER,
  ADD_TO_DEQUE,
  GET_FROM_DEQUE_TO_OPEN_BRACKET,
  ADD_UNARY
};



Poliz::Poliz(std::string str) {
  this->base_str_ = str;
  ConverToPoliz(str);
}

void Poliz::ConverToPoliz(std::string str) {
  std::deque<char> main_deque;
  std::string poliz_str;
  char previous_symbol = NULL;
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
  return Bdouble(0.0);
}

std::string Poliz::GetBaseStr() const {
  return base_str_;
}

Poliz::SymbolType Poliz::CheckTypeSymbol(char& symbol) {
  if ((symbol >= '0' && symbol <= '9') || symbol == '.') {
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
}

Poliz::ActivitiesWithSymbol Poliz::SelectingAnAction(SymbolType symbol, char& previous_symbol) {
  if (previous_symbol == NULL) {
    if (symbol == SymbolType::NUMBER) {
      return ActivitiesWithSymbol::ADD_WITHOUT_SPACE_TO_ANSWER;
    }
    if (symbol == SymbolType::MINUS) {
      return ActivitiesWithSymbol::ADD_UNARY;
    }
    if (symbol == SymbolType::SIN) {
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
    if (symbol == SymbolType::SIN) {
      return ActivitiesWithSymbol::ADD_UNARY;
    }
    if (symbol == SymbolType::MULTIPLICATION) {
      return ActivitiesWithSymbol::ADD_TO_DEQUE;
    }
    if (symbol == SymbolType::DIVISION) {
      return ActivitiesWithSymbol::ADD_TO_DEQUE;
    }
    if (symbol == SymbolType::DEGREE) {
      return ActivitiesWithSymbol::ADD_TO_DEQUE;
    }
    if (symbol == SymbolType::OPEN_BRACKET) {
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
          main_deque.back() == '-') {
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
          main_deque.back() == '*' || main_deque.back() == '/') {
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
        if (main_deque.back() == '_' || main_deque.back() == '#') {
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
