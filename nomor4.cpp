#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

class MinesweeperGame {
  private:
      static const int MAX_SIZE = 10;

      int board[MAX_SIZE][MAX_SIZE];
      bool revealed[MAX_SIZE][MAX_SIZE];
      bool flagged[MAX_SIZE][MAX_SIZE];

      int size;
      int totalBombs;
      int flagCount;
      int openCount;

      bool gameOver;
      bool gameWon;

      time_t startTime;

      int countNeighborBombs(int r, int c) const {
          int count = 0;
          for (int dr = -1; dr <= 1; dr++) {
              for (int dc = -1; dc <= 1; dc++) {
                  if (dr == 0 && dc == 0) continue;
                  int nr = r + dr, nc = c + dc;
                  if (nr >= 0 && nr < size && nc >= 0 && nc < size) {
                      if (board[nr][nc] == -1) count++;
                  }
              }
          }
          return count;
      }

      void floodFill(int r, int c) {
          if (r < 0 || r >= size || c < 0 || c >= size) return;
          if (revealed[r][c] || flagged[r][c]) return;
          if (board[r][c] == -1) return;

          revealed[r][c] = true;
          openCount++;

          if (board[r][c] == 0) {
              for (int dr = -1; dr <= 1; dr++)
                  for (int dc = -1; dc <= 1; dc++)
                      if (!(dr == 0 && dc == 0))
                          floodFill(r + dr, c + dc);
          }
      }

      void displayBoard(bool revealAll = false) const {
          int elapsed = (int)difftime(time(nullptr), startTime);
          std::cout << "\n  Bom tersisa: " << (totalBombs - flagCount) << "   |   Waktu: " << elapsed << " detik\n\n     ";

          for (int c = 1; c < size+1; c++){
            std::cout << " " << (c) << (c < 10 ? " " : "");
          }
          std::cout << "\n    +";
          for (int c = 0; c < size; c++) std::cout << "---";
          std::cout << "+\n";

          for (int r = 0; r < size; r++) {
              std::cout << (r + 1 < 10 ? " " : "") << (r + 1) << "  |";
              for (int c = 0; c < size; c++) {
                  if (revealAll && board[r][c] == -1) std::cout << (flagged[r][c] ? " F " : " * ");
                  else if (flagged[r][c]) std::cout << " F ";
                  else if (!revealed[r][c]) std::cout << " . ";
                  else std::cout << (board[r][c] == 0 ? "   " : " " + std::to_string(board[r][c]) + " ");
              }
              std::cout << "|\n";
          }
          std::cout << "    +";
          for (int c = 0; c < size; c++) std::cout << "---";
          std::cout << "+\n";
      }

      void placeBombs() {
          int placed = 0;
          while (placed < totalBombs) {
              int r = rand() % size, c = rand() % size;
              if (board[r][c] != -1) {
                  board[r][c] = -1;
                  placed++;
              }
          }
          for (int r = 0; r < size; r++)
              for (int c = 0; c < size; c++)
                  if (board[r][c] != -1) board[r][c] = countNeighborBombs(r, c);
      }

      void init() {
          for (int r = 0; r < size; r++)
              for (int c = 0; c < size; c++) {
                  board[r][c] = 0;
                  revealed[r][c] = false;
                  flagged[r][c] = false;
              }
          flagCount = 0; openCount = 0; gameOver = false; gameWon = false;
      }

      void checkWin() {
          if (gameOver) return;
          for (int r = 0; r < size; r++)
              for (int c = 0; c < size; c++)
                  if ((board[r][c] == -1 && !flagged[r][c]) || (board[r][c] != -1 && flagged[r][c])) return;
          gameWon = gameOver = true;
      }

      int inputInt(const std::string& prompt, int lo, int hi) const {
          int val;
          while (true) {
              std::cout << prompt;
              if (std::cin >> val && val >= lo && val <= hi) return val;
              std::cin.clear();
              std::cin.ignore(10000, '\n');
              std::cout << "  [!] Input tidak valid.\n";
          }
      }

  public:
      MinesweeperGame() : size(0), totalBombs(0), flagCount(0), openCount(0), gameOver(false), gameWon(false) {
          srand((unsigned)time(nullptr));
      }

      void setup() {
          size = inputInt("  Ukuran papan (4-10): ", 4, MAX_SIZE);
          totalBombs = inputInt("  Jumlah bom (1-" + std::to_string(size * size - 1) + "): ", 1, size * size - 1);
          init();
          placeBombs();
          startTime = time(nullptr);
      }

      void play() {
          while (!gameOver) {
              displayBoard();
              char action;
              std::cout << "\n  Aksi (O/F): "; std::cin >> action;
              action = (char)toupper((unsigned char)action);

              int r = inputInt("  Baris: ", 1, size) - 1;
              int c = inputInt("  Kolom: ", 1, size) - 1;

              if (action == 'O') {
                  if (revealed[r][c] || flagged[r][c]) continue;
                  if (board[r][c] == -1) {
                      revealed[r][c] = true; gameOver = true;
                      displayBoard(true);
                      std::cout << "\n GAME OVER \n";
                  } else {
                      floodFill(r, c);
                      checkWin();
                  }
              } else if (action == 'F') {
                  if (revealed[r][c]) continue;
                  flagged[r][c] = !flagged[r][c];
                  flagCount += (flagged[r][c] ? 1 : -1);
                  checkWin();
              }
          }
          if (gameWon) {
              displayBoard(true);
              std::cout << "\n  SELAMAT! Kamu menang!\n";
          }
      }

      void mainMenu() {
          while (true) {
            std::cout << "\n1. Mulai Baru\n2. Keluar\nPilih: ";
            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            if (choice == 1) {
                setup(); play();
            }
            else if (choice == 2) break;
          }
      }
};

int main() {
    MinesweeperGame game;
    game.mainMenu();
    return 0;
}