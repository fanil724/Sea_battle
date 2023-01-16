#include <iostream>
#include <random>

enum Hit_Status {
    Indefinitely,
    Hit = 1,
    Miss = -1,
    Terminated = 0
};

struct Cell {
    Hit_Status hit;
    int Ship_ID;
};

bool ship(Cell **&Player, size_t size, int x, int y, int a, int b) {
    int i = 0, j = 0;
    if (y == b) {
        if (x < a) {
            i = x;
            j = a;
        } else if (x > a) {
            i = a;
            j = x;
        }
        for (; i < j; i++) {
            if (Player[i][y].Ship_ID != 0) {
                return false;
            }
        }
        if (x == a) {
            if (y < b) {
                i = y;
                j = b;
            } else if (y > b) {
                i = b;
                j = y;
            }
            for (; i < j; i++) {
                if (Player[x][i].Ship_ID != 0) {
                    return false;
                }
            }
        }
        return true;
    }
}

void random_placement_of_ships(Cell **&Player, size_t size) {
    std::random_device rand;
    int ship_size = 4, count_of_ships = 1;
    for (int j = ship_size; j > 0; j--) {
        int count = 0;
        for (int i = count_of_ships; i < 5; i++) {
            std::uniform_int_distribution<int> disribution(0, 9);
            int x = disribution(rand);
            int y = disribution(rand);
            std::uniform_int_distribution<int> disr(1, 4);
            int direction = disr(rand);
            std::cout << x << " " << y << " " << direction << std::endl;
            switch (direction) {
                case 1:
                    if (ship(Player, size, x, y, x + ship_size, y) && ((x + ship_size) < size)) {
                        for (int c = x; c < (x + ship_size); c++) {
                            Player[c][y].Ship_ID = ship_size;
                        }
                        std::cout << "1\n";
                    } else { i--; }
                    break;
                case 2:
                    if (ship(Player, size, x, y, x - ship_size, y) && ((x - ship_size) > -1)) {
                        for (int c = x - ship_size; c < x; c++) {
                            Player[c][y].Ship_ID = ship_size;
                        }
                        std::cout << "2\n";
                    } else { i--; }
                    break;
                case 3:
                    if (ship(Player, size, x, y, x, y - ship_size) && ((y - ship_size) > -1)) {
                        for (int c = y - ship_size; c < y; c++) {
                            Player[x][c].Ship_ID = ship_size;
                        }
                        std::cout << "3\n";
                    } else { i--; }
                    break;
                case 4:
                    if (ship(Player, size, x, y, x, y + ship_size) && ((y + ship_size) < size)) {
                        for (int c = y; c < (y + ship_size); c++) {
                            Player[x][c].Ship_ID = ship_size;
                        }
                        std::cout << "4\n";
                    } else { i--; }
                    break;
            }
        }
    }
}

void Print_Sea_Battlw_for_PC(Cell **Player, size_t size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << Player[i][j].hit << " ";
        }
        std::cout << std::endl;
    }
}

void Print_Sea_Battlw_for_Player(Cell **Player, size_t size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (Player[i][j].Ship_ID != 0) {
                std::cout << Player[i][j].Ship_ID << " ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}


int main() {
    const size_t size = 10;
    Cell **player = new Cell *[size];
    for (int i = 0; i < size; i++) {
        player[i] = new Cell[size]{Indefinitely, 0};
    }
    Cell **pc = new Cell *[size];
    for (int i = 0; i < size; i++) {
        pc[i] = new Cell[size]{Indefinitely, 0};
    }
    random_placement_of_ships(player, size);
    Print_Sea_Battlw_for_Player(player, size);
}

