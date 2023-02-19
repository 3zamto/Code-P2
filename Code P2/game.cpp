// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T13L
// Names: MOHAMED MAHMOUD ABDELAZIM ABOUELMAATI | SULTAN ABDULLAH SALEM BAHASAN | ALI AHMED ALI AL SILLAK
// IDs: 1211306765 | 1211306562 | 1211306219
// Emails: 1211306765@student.mmu.edu.my | 1211306562@student.mmu.edu.my  |  1211306219@student.mmu.edu.my 
// Phones: 0176767433 | 01121638849 | 01139714584
// *********************************************************

#include <iostream>

void DrawBoard(const int& height, const int& width, const std::vector<std::vector<std::string>>& data) {
  std::cout << ".: Alien VS Zombies :." << std::endl;
  for (int i = 0, row = 0; i < (height * 2) + 1; i++) {
    if (i % 2 == 0) {
      std::cout << "  ";
      for (int j = 0; j < width; j++)
        std::cout << "+-";
      std::cout << "+" << std::endl;
    }
    else {
      std::cout << row + 1 << " |";
      for (int j = 0, col = 0; j < width; j++, col++)
        std::cout << data[row][col] << "|";
      std::cout << std::endl;
      row += 1;
    }
  }

  if (width > 9) {
    std::cout << "  ";
    for (int i = 0; i < 9; i++) std::cout << "  ";
    for (int i = 10; i <= width; i++) std::cout << " " << (int)(i / 10);
    std::cout << std::endl;
  }
  std::cout << "  ";
  for (int i = 0, j = 1; i < width; i++, j++) {
    if (j % 10 == 0) j = 0;
    std::cout << " " << j;
  }
  std::cout << std::endl << std::endl;
}
