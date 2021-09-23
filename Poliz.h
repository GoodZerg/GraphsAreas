#pragma once

#include "Header.h"

class Poliz {
public:
  Poliz(std::string str);
  void ConverToPoliz(std::string str);
  Bdouble GetY(Bdouble x ) const;
  std::string GetBaseStr() const;
private:
  enum class SymbolType;
  enum class ActivitiesWithSymbol;
  
  std::string poliz_ = "";
  std::string base_str_ = "";

  SymbolType CheckTypeSymbol(char& symbol);
  ActivitiesWithSymbol SelectingAnAction(SymbolType symbol, char& previous_symbol);
  void DoAnAction(ActivitiesWithSymbol activity, std::deque<char>& main_deque, 
    std::string& polis_string, SymbolType symbol_type, char& symbol);
};

