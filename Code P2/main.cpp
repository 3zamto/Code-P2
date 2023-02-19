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
#include <vector>
#include <fstream>
#include <sstream>

#include "pf/helper.h"
#include "game.cpp"
#include "utils.cpp"

int main() {
  int ROW = 0;
  int COL = 0;
  int ZOMBIES = 0;

  std::cout << "New Game Settings" << std::endl;
  std::cout << "Enter Row Count (Odd Number): ";
  std::cin >> ROW;
  std::cout << "Enter Column Count (Odd Number): ";
  std::cin >> COL;
  std::cout << "Enter Zombies Count (1-9): ";
  std::cin >> ZOMBIES;

  if (ROW % 2 == 0 || COL % 2 == 0 || ZOMBIES < 1 || ZOMBIES > 9) {
    std::cout << "Row and Column Should Be Odd Number!" << std::endl
      << "Zombies Should Be Between 1-9!" << std::endl
      << "Try Again!" << std::endl;
    return 0;
  }

  int currentCol = COL / 2; // 5
  int currentRow = ROW / 2; // 2

  std::vector<std::string> objects({ "^", "v", "<", ">", "h", "p", "r", " ", "X" });
  std::vector<std::vector<Cell>> cell(ROW, std::vector<Cell>(COL));

  cell[ROW / 2][COL / 2].SetAppearance("A");
  cell[ROW / 2][COL / 2].SetCharacter(true);
  cell[ROW / 2][COL / 2].SetLife(100);
  cell[ROW / 2][COL / 2].SetAttack(0);

  for (int i = 0; i < ZOMBIES; i++) {
    const int attack[6] = { 10, 20, 30 };
    const int life[6] = { 100, 150, 170, 200, 250, 300 };
    int x = utils::GetRandomNumber(0, ROW - 1);
    int y = utils::GetRandomNumber(0, COL - 1);
    cell[x][y].SetAppearance(std::to_string(i + 1));
    cell[x][y].SetLife(life[utils::GetRandomNumber(0, 5)]);
    cell[x][y].SetAttack(attack[utils::GetRandomNumber(0, 2)]);
    cell[x][y].SetRange(utils::GetRandomNumber(1, ROW > COL ? ROW : COL));
    cell[x][y].SetCharacter(true);
  }

  std::string command = "";
  bool isAlienMove = true;
  bool isZombieMove = false;
  bool takeCommand = true;
  int zombieNumber = 0;
  bool isFirstRender = true;

  while (true) {
    if (isAlienMove) zombieNumber = 0;

    if (isZombieMove) {
      if (zombieNumber == ZOMBIES) {
        isZombieMove = false;
        isAlienMove = true;
        takeCommand = true;
        zombieNumber = 1;
      }
      else {
        isAlienMove = false;
        takeCommand = false;
        isZombieMove = true;
        zombieNumber++;
      }
    }

    pf::ClearScreen();

    std::vector<std::vector<std::string>> data(ROW, std::vector<std::string>(COL));
    bool isAlienDied = false;
    for (int i = 0; i < ROW; i++) {
      for (int j = 0; j < COL; j++) {
        if (cell[i][j].GetAppearance() == "-1" || (isZombieMove && cell[i][j].GetAppearance() == ".")) {
          if (isFirstRender) {
            cell[i][j].SetAppearance(objects[utils::GetRandomNumber(0, objects.size() - 1)]);
          }
          else {
            cell[i][j].SetAppearance(objects[utils::GetRandomNumber(0, objects.size() - 2)]);
          }
        }

        if (cell[i][j].GetAppearance() == "A") {
          isAlienDied = cell[i][j].GetLife() <= 0;
        }

        data[i][j] = cell[i][j].GetLife() > 0 || cell[i][j].GetLife() == -1 ? cell[i][j].GetAppearance() : " ";
        cell[i][j].SetObject(true);
      }
    }

    if (isFirstRender) isFirstRender = false;

    DrawBoard(ROW, COL, data);
    for (int i = 0; i < ROW; i++) {
      for (int j = 0; j < COL; j++) {
        if (cell[i][j].GetAppearance() == "A") {
          if (isAlienMove) {
            std::cout << "-->  ";
          }
          else {
            std::cout << "     ";
          }
          std::cout << "ALIEN:         Attack = " << cell[i][j].GetAttack()
            << "\tLife = " << cell[i][j].GetLife() << std::endl;
          break;
        }
      }
    }

    for (int x = 1; x < 10; x++) {
      for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
          if (cell[i][j].GetAppearance() == std::to_string(x)) {
            if (isZombieMove && zombieNumber == x) {
              std::cout << "-->  ";
            }
            else {
              std::cout << "     ";
            }
            std::cout << "ZOMBIE " << x << ":      Attack = " << cell[i][j].GetAttack()
              << "\tLife = " << cell[i][j].GetLife()
              << "\tRange = " << cell[i][j].GetRange() << std::endl;
            break;
          }
        }
      }
    }

    if (isAlienDied) {
      std::cout << "Alien Died" << std::endl;
      pf::Pause();
      break;
    }

    if (isAlienMove) {
      for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
          if (cell[i][j].GetAppearance() == "A") {
            currentRow = i;
            currentCol = j;
            break;
          }
        }
      }
    }

    if (isZombieMove) {
      for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
          if (cell[i][j].GetAppearance() == std::to_string(zombieNumber)) {
            currentRow = i;
            currentCol = j;
            break;
          }
        }
      }
    }

    if (takeCommand && isAlienMove) {
      std::cout << "Enter Command: ";
      std::cin >> command;
    }
    else if (isAlienMove) {
      takeCommand = true;
      isAlienMove = true;
      isZombieMove = false;
    }

    if (isZombieMove) {
      std::vector<std::string> commands({ "up", "down", "left", "right" });
      command = commands[utils::GetRandomNumber(0, commands.size() - 1)];

      // to reset the ALIEN attack value
      int r = 0, c = 0;
      for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
          if (cell[i][j].GetAppearance() == "A") {
            cell[i][j].SetAttack(0);
            r = i;
            c = j;
            break;
          }
        }
      }

      int range = 0;
      int damage = 0;
      int r1 = 0, c1 = 0;
      for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
          if (cell[i][j].GetAppearance() == std::to_string(zombieNumber)) {
            range = cell[i][j].GetRange();
            damage = cell[i][j].GetAttack();
            r1 = i;
            c1 = j;
            break;
          }
        }
      }

      for (int i = 0; i < range; i++) {
        if (((r1 + i) < ROW && (r1 + i) == r) || ((r1 - i) > -1 && (r1 - i) == r) ||
          ((c1 + i) < COL && (c1 - i) == c) || ((c1 - i) > -1 && (c1 - i) == c)) {
          cell[r][c].SetLife(cell[r][c].GetLife() - damage);
          break;
        }
      }
    }

    if (utils::ToLowerCase(command) == "up") {
      if (currentRow - 1 > -1) {
        if (isAlienMove) {
          std::cout << "Alien Moved UP!" << std::endl;
        }
        else if (isZombieMove) {
          std::cout << "Zombie " << (zombieNumber == 0 ? 1 : zombieNumber) << " Moved UP!" << std::endl;
        }

        short attack = cell[currentRow][currentCol].GetAttack();
        short life = cell[currentRow][currentCol].GetLife();
        std::string patch = cell[currentRow][currentCol].GetAppearance();

        if (!(int(cell[currentRow - 1][currentCol].GetAppearance()[0]) > 48
          && int(cell[currentRow - 1][currentCol].GetAppearance()[0]) < 58)) {
          if (isAlienMove)
            utils::MakeMove(cell, ".", true, false, currentRow, currentCol);
          else if (isZombieMove)
            utils::MakeMove(cell, " ", true, false, currentRow, currentCol);
        }
        else if (isZombieMove) {
          utils::MakeMove(cell, " ", true, false, currentRow, currentCol);
        }
        currentRow = currentRow - 1;

        std::string value = cell[currentRow][currentCol].GetAppearance();
        if (int(value[0]) > 48 && int(value[0]) < 58) {
          bool flag = false;
          for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
              if (cell[i][j].GetAppearance() == value) {
                cell[i][j].SetLife(cell[i][j].GetLife() - attack);
                if (cell[i][j].GetLife() > 0) {
                  isAlienMove = false;
                  isZombieMove = true;
                  takeCommand = false;
                }
                else {
                  utils::MakeMove(cell, "A", false, true, i, j);
                  cell[i][j].SetLife(life);
                }
                flag = true;
                break;
              }
            }
            if (flag) break;
          }
        }
        else if (value == "A") {
          cell[currentRow][currentCol].SetLife(cell[currentRow][currentCol].GetLife() - attack);
          cell[currentRow + 1][currentCol].SetAppearance(patch);
          isAlienMove = true;
          isZombieMove = false;
          takeCommand = true;
        }
        else {
          if (value != "r" && isAlienMove)
            utils::MakeMove(cell, "A", false, true, currentRow, currentCol);
          else if (value != "r" && isZombieMove)
            utils::MakeMove(cell, std::to_string(zombieNumber), false, true, currentRow, currentCol);

          if (value == "^" || value == "<" || value == ">" || value == "v") {
            if (isAlienMove) attack += 20;

            if (value == "^") command = "up";
            else if (value == "v") command = "down";
            else if (value == "<") command = "left";
            else if (value == ">") command = "right";

            takeCommand = false;
          }
          else if (value == "p") {
            bool isDone = false;
            int row = ROW, col = COL;

            for (int i = currentRow; i < row; i++) {
              col = COL;
              for (int j = currentCol; j < col; j++) {
                if (int(cell[i][j].GetAppearance()[0]) > 48
                  && int(cell[i][j].GetAppearance()[0]) < 58) {
                  cell[i][j].SetLife(cell[i][j].GetLife() - 10);
                  isDone = true;
                  break;
                }
                if (j == COL - 1) { j = -1; col = currentCol; }
              }
              if (isDone) break;
              if (i == ROW - 1) { i = -1; row = currentRow; }
            }

            takeCommand = false;
          }
          else if (value == "r") {
            std::vector<std::string> objs({ "^", "v", "<", ">", "h", "p" });
            utils::MakeMove(cell, objs[utils::GetRandomNumber(0, objs.size() - 1)], true, false, currentRow, currentCol);
            currentRow = currentRow + 1;

            if (isAlienMove)
              utils::MakeMove(cell, "A", false, true, currentRow, currentCol);
            else if (isZombieMove)
              utils::MakeMove(cell, std::to_string(zombieNumber), false, true, currentRow, currentCol);

            isAlienMove = false;
            isZombieMove = true;
            takeCommand = false;

            cell[currentRow][currentCol].SetAttack(attack);
            cell[currentRow][currentCol].SetLife(life);

            continue;
          }
          else if (value == "h") {
            if (isAlienMove) life += 20;
            takeCommand = false;
          }
          else if (value == " " || value == ".") {
            takeCommand = false;
            std::vector<std::string> commands({ "up", "down", "left", "right" });
            command = commands[utils::GetRandomNumber(0, commands.size() - 1)];
            // continue;
          }
          else if (value == "X") {
            life = 0;
          }

          cell[currentRow][currentCol].SetAttack(attack);
          cell[currentRow][currentCol].SetLife(life);

          isAlienMove = true;
          if (zombieNumber == ZOMBIES) {
            zombieNumber = 1;
            isZombieMove = false;
          }

        }
      }
      else {
        isAlienMove = false;
        isZombieMove = true;
        takeCommand = false;
        std::cout << "Alien Turn Gone..." << std::endl;
        std::cout << "Zombie " << (zombieNumber == 0 ? 1 : zombieNumber) << " Got Turn..." << std::endl;
      }
    }
    else if (utils::ToLowerCase(command) == "down") {
      if (currentRow + 1 < ROW) {
        if (isAlienMove) {
          std::cout << "Alien Moved DOWN!" << std::endl;
        }
        else if (isZombieMove) {
          std::cout << "Zombie " << (zombieNumber == 0 ? 1 : zombieNumber) << " Moved DOWN!" << std::endl;
        }

        short attack = cell[currentRow][currentCol].GetAttack();
        short life = cell[currentRow][currentCol].GetLife();
        std::string patch = cell[currentRow][currentCol].GetAppearance();

        if (!(int(cell[currentRow + 1][currentCol].GetAppearance()[0]) > 48
          && int(cell[currentRow + 1][currentCol].GetAppearance()[0]) < 58)) {
          if (isAlienMove)
            utils::MakeMove(cell, ".", true, false, currentRow, currentCol);
          else if (isZombieMove)
            utils::MakeMove(cell, " ", true, false, currentRow, currentCol);
        }
        else if (isZombieMove) {
          utils::MakeMove(cell, " ", true, false, currentRow, currentCol);
        }
        currentRow = currentRow + 1;

        std::string value = cell[currentRow][currentCol].GetAppearance();
        if (int(value[0]) > 48 && int(value[0]) < 58) {
          bool flag = false;
          for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
              if (cell[i][j].GetAppearance() == value) {
                cell[i][j].SetLife(cell[i][j].GetLife() - attack);
                if (cell[i][j].GetLife() > 0) {
                  isAlienMove = false;
                  isZombieMove = true;
                  takeCommand = false;
                }
                else {
                  utils::MakeMove(cell, "A", false, true, i, j);
                  cell[i][j].SetLife(life);
                }
                flag = true;
                break;
              }
            }
            if (flag) break;
          }
        }
        else if (value == "A") {
          cell[currentRow][currentCol].SetLife(cell[currentRow][currentCol].GetLife() - attack);
          cell[currentRow - 1][currentCol].SetAppearance(patch);
          isAlienMove = true;
          isZombieMove = false;
          takeCommand = true;
        }
        else {
          if (value != "r" && isAlienMove)
            utils::MakeMove(cell, "A", false, true, currentRow, currentCol);
          else if (value != "r" && isZombieMove)
            utils::MakeMove(cell, std::to_string(zombieNumber), false, true, currentRow, currentCol);

          if (value == "^" || value == "<" || value == ">" || value == "v") {
            if (isAlienMove) attack += 20;

            if (value == "^") command = "up";
            else if (value == "v") command = "down";
            else if (value == "<") command = "left";
            else if (value == ">") command = "right";

            takeCommand = false;
          }
          else if (value == "p") {
            bool isDone = false;
            int row = ROW, col = COL;

            for (int i = currentRow; i < row; i++) {
              col = COL;
              for (int j = currentCol; j < col; j++) {
                if (int(cell[i][j].GetAppearance()[0]) > 48
                  && int(cell[i][j].GetAppearance()[0]) < 58) {
                  cell[i][j].SetLife(cell[i][j].GetLife() - 10);
                  isDone = true;
                  break;
                }
                if (j == COL - 1) { j = -1; col = currentCol; }
              }
              if (isDone) break;
              if (i == ROW - 1) { i = -1; row = currentRow; }
            }

            takeCommand = false;
          }
          else if (value == "r") {
            std::vector<std::string> objs({ "^", "v", "<", ">", "h", "p" });
            utils::MakeMove(cell, objs[utils::GetRandomNumber(0, objs.size() - 1)], true, false, currentRow, currentCol);
            currentRow = currentRow - 1;

            if (isAlienMove)
              utils::MakeMove(cell, "A", false, true, currentRow, currentCol);
            else if (isZombieMove)
              utils::MakeMove(cell, std::to_string(zombieNumber), false, true, currentRow, currentCol);

            isAlienMove = false;
            isZombieMove = true;
            takeCommand = false;

            cell[currentRow][currentCol].SetAttack(attack);
            cell[currentRow][currentCol].SetLife(life);
            continue;
          }
          else if (value == "h") {
            if (isAlienMove) life += 20;
            takeCommand = false;
          }
          else if (value == " " || value == ".") {
            takeCommand = false;
            std::vector<std::string> commands({ "up", "down", "left", "right" });
            command = commands[utils::GetRandomNumber(0, commands.size() - 1)];
            // continue;
          }
          else if (value == "X") {
            life = 0;
          }

          cell[currentRow][currentCol].SetAttack(attack);
          cell[currentRow][currentCol].SetLife(life);

          isAlienMove = true;
          if (zombieNumber == ZOMBIES) {
            zombieNumber = 1;
            isZombieMove = false;
          }

        }
      }
      else {
        isAlienMove = false;
        isZombieMove = true;
        takeCommand = false;
        std::cout << "Alien Turn Gone..." << std::endl;
        std::cout << "Zombie " << (zombieNumber == 0 ? 1 : zombieNumber) << " Got Turn..." << std::endl;
      }
    }
    else if (utils::ToLowerCase(command) == "left") {
      if (currentCol - 1 > -1) {
        if (isAlienMove) {
          std::cout << "Alien Moved LEFT!" << std::endl;
        }
        else if (isZombieMove) {
          std::cout << "Zombie " << (zombieNumber == 0 ? 1 : zombieNumber) << " Moved LEFT!" << std::endl;
        }

        short attack = cell[currentRow][currentCol].GetAttack();
        short life = cell[currentRow][currentCol].GetLife();
        std::string patch = cell[currentRow][currentCol].GetAppearance();

        if (!(int(cell[currentRow][currentCol - 1].GetAppearance()[0]) > 48
          && int(cell[currentRow][currentCol - 1].GetAppearance()[0]) < 58)) {
          if (isAlienMove)
            utils::MakeMove(cell, ".", true, false, currentRow, currentCol);
          else if (isZombieMove)
            utils::MakeMove(cell, " ", true, false, currentRow, currentCol);
        }
        else if (isZombieMove) {
          utils::MakeMove(cell, " ", true, false, currentRow, currentCol);
        }
        currentCol = currentCol - 1;

        std::string value = cell[currentRow][currentCol].GetAppearance();
        if (int(value[0]) > 48 && int(value[0]) < 58) {
          bool flag = false;
          for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
              if (cell[i][j].GetAppearance() == value) {
                cell[i][j].SetLife(cell[i][j].GetLife() - attack);
                if (cell[i][j].GetLife() > 0) {
                  isAlienMove = false;
                  isZombieMove = true;
                  takeCommand = false;
                }
                else {
                  utils::MakeMove(cell, "A", false, true, i, j);
                  cell[i][j].SetLife(life);
                }
                flag = true;
                break;
              }
            }
            if (flag) break;
          }
        }
        else if (value == "A") {
          cell[currentRow][currentCol].SetLife(cell[currentRow][currentCol].GetLife() - attack);
          cell[currentRow][currentCol + 1].SetAppearance(patch);
          isAlienMove = true;
          isZombieMove = false;
          takeCommand = true;
        }
        else {
          if (value != "r" && isAlienMove)
            utils::MakeMove(cell, "A", false, true, currentRow, currentCol);
          else if (value != "r" && isZombieMove)
            utils::MakeMove(cell, std::to_string(zombieNumber), false, true, currentRow, currentCol);

          if (value == "^" || value == "<" || value == ">" || value == "v") {
            if (isAlienMove) attack += 20;

            if (value == "^") command = "up";
            else if (value == "v") command = "down";
            else if (value == "<") command = "left";
            else if (value == ">") command = "right";

            takeCommand = false;
          }
          else if (value == "p") {
            bool isDone = false;
            int row = ROW, col = COL;

            for (int i = currentRow; i < row; i++) {
              col = COL;
              for (int j = currentCol; j < col; j++) {
                if (int(cell[i][j].GetAppearance()[0]) > 48
                  && int(cell[i][j].GetAppearance()[0]) < 58) {
                  cell[i][j].SetLife(cell[i][j].GetLife() - 10);
                  isDone = true;
                  break;
                }
                if (j == COL - 1) { j = -1; col = currentCol; }
              }
              if (isDone) break;
              if (i == ROW - 1) { i = -1; row = currentRow; }
            }

            takeCommand = false;
          }
          else if (value == "r") {
            std::vector<std::string> objs({ "^", "v", "<", ">", "h", "p" });
            utils::MakeMove(cell, objs[utils::GetRandomNumber(0, objs.size() - 1)], true, false, currentRow, currentCol);
            currentCol = currentCol + 1;

            if (isAlienMove)
              utils::MakeMove(cell, "A", false, true, currentRow, currentCol);
            else if (isZombieMove)
              utils::MakeMove(cell, std::to_string(zombieNumber), false, true, currentRow, currentCol);

            isAlienMove = false;
            isZombieMove = true;
            takeCommand = false;

            cell[currentRow][currentCol].SetAttack(attack);
            cell[currentRow][currentCol].SetLife(life);
            continue;
          }
          else if (value == "h") {
            if (isAlienMove) life += 20;
            takeCommand = false;
          }
          else if (value == " " || value == ".") {
            takeCommand = false;
            std::vector<std::string> commands({ "up", "down", "left", "right" });
            command = commands[utils::GetRandomNumber(0, commands.size() - 1)];
            // continue;
          }
          else if (value == "X") {
            life = 0;
          }

          cell[currentRow][currentCol].SetAttack(attack);
          cell[currentRow][currentCol].SetLife(life);

          isAlienMove = true;
          if (zombieNumber == ZOMBIES) {
            zombieNumber = 1;
            isZombieMove = false;
          }
        }
      }
      else {
        isAlienMove = false;
        isZombieMove = true;
        takeCommand = false;
        std::cout << "Alien Turn Gone..." << std::endl;
        std::cout << "Zombie " << (zombieNumber == 0 ? 1 : zombieNumber) << " Got Turn..." << std::endl;
      }
    }
    else if (utils::ToLowerCase(command) == "right") {
      if (currentCol + 1 < COL) {
        if (isAlienMove) {
          std::cout << "Alien Moved RIGHT!" << std::endl;
        }
        else if (isZombieMove) {
          std::cout << "Zombie " << (zombieNumber == 0 ? 1 : zombieNumber) << " Moved RIGHT!" << std::endl;
        }

        short attack = cell[currentRow][currentCol].GetAttack();
        short life = cell[currentRow][currentCol].GetLife();
        std::string patch = cell[currentRow][currentCol].GetAppearance();

        if (!(int(cell[currentRow][currentCol + 1].GetAppearance()[0]) > 48
          && int(cell[currentRow][currentCol + 1].GetAppearance()[0]) < 58)) {
          if (isAlienMove)
            utils::MakeMove(cell, ".", true, false, currentRow, currentCol);
          else if (isZombieMove)
            utils::MakeMove(cell, " ", true, false, currentRow, currentCol);
        }
        else if (isZombieMove) {
          utils::MakeMove(cell, " ", true, false, currentRow, currentCol);
        }
        currentCol = currentCol + 1;

        std::string value = cell[currentRow][currentCol].GetAppearance();

        if (int(value[0]) > 48 && int(value[0]) < 58) {
          bool flag = false;
          for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
              if (cell[i][j].GetAppearance() == value) {
                cell[i][j].SetLife(cell[i][j].GetLife() - attack);
                if (cell[i][j].GetLife() > 0) {
                  isAlienMove = false;
                  isZombieMove = true;
                  takeCommand = false;
                }
                else {
                  utils::MakeMove(cell, "A", false, true, i, j);
                  cell[i][j].SetLife(life);
                }
                flag = true;
                break;
              }
            }
            if (flag) break;
          }
        }
        else if (value == "A") {
          cell[currentRow][currentCol].SetLife(cell[currentRow][currentCol].GetLife() - attack);
          cell[currentRow][currentCol - 1].SetAppearance(patch);
          isAlienMove = true;
          isZombieMove = false;
          takeCommand = true;
        }
        else {
          if (value != "r" && isAlienMove)
            utils::MakeMove(cell, "A", false, true, currentRow, currentCol);
          else if (value != "r" && isZombieMove)
            utils::MakeMove(cell, std::to_string(zombieNumber), false, true, currentRow, currentCol);

          if (value == "^" || value == "<" || value == ">" || value == "v") {
            if (isAlienMove) attack += 20;

            if (value == "^") command = "up";
            else if (value == "v") command = "down";
            else if (value == "<") command = "left";
            else if (value == ">") command = "right";

            takeCommand = false;
          }
          else if (value == "p") {
            bool isDone = false;
            int row = ROW, col = COL;

            for (int i = currentRow; i < row; i++) {
              col = COL;
              for (int j = currentCol; j < col; j++) {
                if (int(cell[i][j].GetAppearance()[0]) > 48
                  && int(cell[i][j].GetAppearance()[0]) < 58) {
                  cell[i][j].SetLife(cell[i][j].GetLife() - 10);
                  isDone = true;
                  break;
                }
                if (j == COL - 1) { j = -1; col = currentCol; }
              }
              if (isDone) break;
              if (i == ROW - 1) { i = -1; row = currentRow; }
            }

            takeCommand = false;
          }
          else if (value == "r") {
            std::vector<std::string> objs({ "^", "v", "<", ">", "h", "p" });
            utils::MakeMove(cell, objs[utils::GetRandomNumber(0, objs.size() - 1)], true, false, currentRow, currentCol);
            currentCol = currentCol - 1;

            if (isAlienMove)
              utils::MakeMove(cell, "A", false, true, currentRow, currentCol);
            else if (isZombieMove)
              utils::MakeMove(cell, std::to_string(zombieNumber), false, true, currentRow, currentCol);

            isAlienMove = false;
            isZombieMove = true;
            takeCommand = false;

            cell[currentRow][currentCol].SetAttack(attack);
            cell[currentRow][currentCol].SetLife(life);
            continue;
          }
          else if (value == "h") {
            if (isAlienMove) life += 20;
            takeCommand = false;
          }
          else if (value == " " || value == ".") {
            takeCommand = false;
            std::vector<std::string> commands({ "up", "down", "left", "right" });
            command = commands[utils::GetRandomNumber(0, commands.size() - 1)];
            // continue;
          }
          else if (value == "X") {
            life = 0;
          }

          cell[currentRow][currentCol].SetAttack(attack);
          cell[currentRow][currentCol].SetLife(life);

          isAlienMove = true;
          // isZombieMove = false;
          if (zombieNumber == ZOMBIES) {
            zombieNumber = 1;
            isZombieMove = false;
          }

        }
      }
      else {
        isAlienMove = false;
        isZombieMove = true;
        takeCommand = false;
        std::cout << "Alien Turn Gone..." << std::endl;
        std::cout << "Zombie " << (zombieNumber == 0 ? 1 : zombieNumber) << " Got Turn..." << std::endl;
      }
    }
    else if (utils::ToLowerCase(command) == "arrow") {
      int row = 0, col = 0;
      std::string value = "";

      std::cout << "Enter Row: ";
      std::cin >> row;
      std::cout << "Enter Column: ";
      std::cin >> col;
      std::cout << "Enter Value: ";
      std::cin >> value;

      row = row - 1;
      col = col - 1;

      if (utils::ToLowerCase(value) == "up") { cell[row][col].SetAppearance("^"); }
      else if (utils::ToLowerCase(value) == "down") { cell[row][col].SetAppearance("v"); }
      else if (utils::ToLowerCase(value) == "left") { cell[row][col].SetAppearance("<"); }
      else if (utils::ToLowerCase(value) == "right") { cell[row][col].SetAppearance(">"); }
      else { std::cout << "Invalid Direction Value!" << std::endl; }
    }
    else if (utils::ToLowerCase(command) == "help") {
      std::cout << "Commands:" << std::endl;
      std::cout << "up - To Move Alien Up" << std::endl;
      std::cout << "down - To Move Alien Down" << std::endl;
      std::cout << "left - To Move Alien Left" << std::endl;
      std::cout << "right - To Move Alien Right" << std::endl;
      std::cout << "arrow - To Switch The Direction Of An Arrow On Game Board" << std::endl;
      std::cout << "help - To See All The Available Commands" << std::endl;
      std::cout << "save - To Save The Current Game" << std::endl;
      std::cout << "load - To Load The Saved Game" << std::endl;
      std::cout << "quit - To Quit The Game While Playing" << std::endl;
    }
    else if (utils::ToLowerCase(command) == "save") {
      std::string data = std::to_string(ROW) + "," + std::to_string(COL) + "," + std::to_string(ZOMBIES) + "," + std::to_string(currentRow) + "," + std::to_string(currentCol) + "\n";
      for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
          data += std::to_string(i) + "," + std::to_string(j) + "," + cell[i][j].GetAppearance() + "," + (cell[i][j].IsObject() ? "t" : "f") + "," + (cell[i][j].IsCharacter() ? "t" : "f") + "," + std::to_string(cell[i][j].GetAttack()) + "," + std::to_string(cell[i][j].GetLife()) + "," + std::to_string(cell[i][j].GetRange()) + "\n";
        }
      }

      std::string filename = "";
      std::cout << "Enter Filename (without any extension): ";
      std::cin.ignore();
      std::getline(std::cin, filename);

      std::ofstream fileOutputStream;
      fileOutputStream.open(filename + ".game", std::ios::out | std::ios::app);
      fileOutputStream << data;
      fileOutputStream.close();
    }
    else if (utils::ToLowerCase(command) == "load") {
      std::string filename = "";
      std::cout << "Enter Filename (without any extension): ";
      std::cin.ignore();
      std::getline(std::cin, filename);

      std::ifstream fileInputStream(filename + ".game");
      std::string line;

      for (int i = 0; std::getline(fileInputStream, line); i++) {
        if (i == 0) {
          std::stringstream ss(line);
          std::string v;
          for (int j = 0; std::getline(ss, v, ','); j++) {
            if (j == 0) ROW = stoi(v);
            else if (j == 1) COL = stoi(v);
            else if (j == 2) ZOMBIES = stoi(v);
            else if (j == 3) currentRow = stoi(v);
            else if (j == 4) currentCol = stoi(v);
          }

          cell.clear();
          for (int j = 0; j < ROW; j++) cell.push_back(std::vector<Cell>(COL));
        }
        else {
          std::stringstream ss(line);
          std::string v;

          int row = 0, col = 0, attack = 0, life = 0, range = 0;
          std::string view = "";
          bool isObject = false;
          bool isCharacter = false;

          for (int j = 0; std::getline(ss, v, ','); j++) {
            if (j == 0) row = stoi(v);
            else if (j == 1) col = stoi(v);
            else if (j == 2) view = v;
            else if (j == 3) isObject = v == "t";
            else if (j == 4) isCharacter = v == "t";
            else if (j == 5) attack = stoi(v);
            else if (j == 6) life = stoi(v);
            else if (j == 7) range = stoi(v);
          }

          cell[row][col].SetAppearance(view);
          cell[row][col].SetAttack(attack);
          cell[row][col].SetLife(life);
          cell[row][col].SetRange(range);
          cell[row][col].SetObject(isObject);
          cell[row][col].SetCharacter(isCharacter);
        }
      }
      fileInputStream.close();
      continue;
    }
    else if (utils::ToLowerCase(command) == "quit") {
      std::string check = "";
      std::cout << "Are You Sure? (y/n) ";
      std::cin >> check;

      check = utils::ToLowerCase(check);

      if (check == "y") {
        return 0;
      }
    }

    pf::Pause();
  }
}