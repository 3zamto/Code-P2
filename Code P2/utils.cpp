// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T13L
// Names: MOHAMED MAHMOUD ABDELAZIM ABOUELMAATI | SULTAN ABDULLAH SALEM BAHASAN | ALI AHMED ALI AL SILLAK
// IDs: 1211306765 | 1211306562 | 1211306219
// Emails: 1211306765@student.mmu.edu.my | 1211306562@student.mmu.edu.my  |  1211306219@student.mmu.edu.my 
// Phones: 0176767433 | 01121638849 | 01139714584
// *********************************************************

#ifndef UTILS_GAME
#define UTILS_GAME

#include <random>
#include <string>
#include "cell.cpp"

namespace utils {
  int GetRandomNumber(const int& min, const int& max) {
    return min + (rand() % static_cast<int>(max - min + 1));
  }

  std::string ToLowerCase(const std::string& str) {
    std::string ret;
    ret.reserve(str.size());
    for (char c : str) ret.push_back(std::tolower(c));
    return ret;
  }

  void MakeMove(std::vector<std::vector<Cell>>& grid, const std::string& appearance,
    const bool& isObject, const bool& isCharacter, const int& row, const int& col) {
    grid[row][col].SetAppearance(appearance);
    grid[row][col].SetObject(isObject);
    grid[row][col].SetCharacter(isCharacter);
  }
}

#endif