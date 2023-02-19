// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T13L
// Names: MOHAMED MAHMOUD ABDELAZIM ABOUELMAATI | SULTAN ABDULLAH SALEM BAHASAN | ALI AHMED ALI AL SILLAK
// IDs: 1211306765 | 1211306562 | 1211306219
// Emails: 1211306765@student.mmu.edu.my | 1211306562@student.mmu.edu.my  |  1211306219@student.mmu.edu.my 
// Phones: 0176767433 | 01121638849 | 01139714584
// *********************************************************
#ifndef CELL_GAME
#define CELL_GAME

#include <string>

class Cell {
private:
  bool isObject;
  bool isCharacter;
  std::string appearance;
  short life;
  short attack;
  short range;

public:
  Cell(): isObject(false), isCharacter(false), appearance("-1"), life(-1), attack(-1), range(3) {}

  bool IsObject() const { return this->isObject; }
  bool IsCharacter() const { return this->isCharacter; }
  const std::string& GetAppearance() const { return this->appearance; }
  short GetLife() const { return this->life; }
  short GetAttack() const { return this->attack; }
  short GetRange() const { return this->range; }

  void SetObject(bool object) { this->isObject = object; }
  void SetCharacter(bool character) { this->isCharacter = character; }
  void SetAppearance(const std::string& appearance) { this->appearance = appearance; }
  void SetLife(short life) { this->life = life; }
  void SetAttack(short attack) { this->attack = attack; }
  void SetRange(short range) { this->range = range; }
};

#endif