#include <iostream>
#include <random>

enum Hit_Status {
    Indefinitely,
    Hit = 1,
    Miss = -1,
    Terminated = 3
};
struct Cell {
    Hit_Status hit;
    int Ship_ID;
};
const int move[4][2]{0, 1, 0, -1, 1, 0, -1, 0};

void ComputerMove(Cell **&Player, size_t size, int x, int y) {
    std::random_device rand;
    int c;
    std::uniform_int_distribution<int> disribution(1, 4);
    c = disribution(rand);
    if (Player[x+move[c][0]][y+move[c][1]].Ship_ID!=0) {
        Player[x+move[c][0]][y+move[c][1]].hit=Hit;
        ComputerMove(Player,size,x+move[c][0],y+move[c][1]);
    }else{
        Player[x+move[c][0]][y+move[c][1]].hit=Miss;
        return;
    }
}

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
        for (int i = 0; i < count_of_ships; i++) {
            int x, y;
            do {
                std::uniform_int_distribution<int> disribution(0, 9);
                x = disribution(rand);
                y = disribution(rand);
            } while (Player[x][y].Ship_ID != 0);
            if (ship(Player, size, x, y, x + ship_size, y) && ((x + ship_size) < size)) {
                for (int c = x; c < (x + ship_size); c++) {
                    Player[c][y].Ship_ID = ship_size;
                }
            } else if (ship(Player, size, x, y, x, y + ship_size) && ((y + ship_size) < size)) {
                for (int c = y; c < (y + ship_size); c++) {
                    Player[x][c].Ship_ID = ship_size;
                }
            } else if (ship(Player, size, x, y, x, y - ship_size) && ((y - ship_size) > -1)) {
                for (int c = y - ship_size; c < y; c++) {
                    Player[x][c].Ship_ID = ship_size;
                }
            } else if (ship(Player, size, x, y, x - ship_size, y) && ((x - ship_size) > -1)) {
                for (int c = x - ship_size; c < x; c++) {
                    Player[c][y].Ship_ID = ship_size;
                }
            } else { i--; }
        }
        count_of_ships++;
        ship_size--;
    }
}

void Player_Turn(Cell **&Player, size_t size) {
    int x, y;
    std::cout << "Select the cell you want to hit:";
    do {
        std::cin >> x >> y;
        if (Player[x][y].hit != Indefinitely) {
            std::cout << "You have already hit this cell, choose another:";
        }
    } while (Player[x][y].hit != Indefinitely);
    if (Player[x][y].Ship_ID != 0) {
        Player[x][y].hit = Hit;
        Player_Turn(Player, size);
    } else {
        Player[x][y].hit = Miss;
        return;
    }
}

void Computer_Shot(Cell **&Player, size_t size) {
    std::random_device rand;
    int x, y;
    do {
        std::uniform_int_distribution<int> disribution(0, 9);
        x = disribution(rand);
        y = disribution(rand);
    } while (Player[x][y].Ship_ID != 0);
    if (Player[x][y].Ship_ID != 0) {
        Player[x][y].hit = Hit;
        ComputerMove(Player,size,x,y);
    } else {
        Player[x][y].hit = Miss;
    }
}

void Print_Sea_Battlw_for_PC(Cell **&Player, size_t size) {
    std::cout << "      Computer field!\n";
    std::cout << "    ";
    for (int i = 0; i < size; i++) {
        std::cout << i + 1 << " ";
    }
    std::cout << std::endl;
    std::cout << "   ";
    for (int i = 0; i < 22; i++) {
        if (i == 0) {
            std::cout << char(218);
        } else if (i == 21) {
            std::cout << char(191);
        } else {
            std::cout << char(196);
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < size; i++) {
        if (i != size - 1) { std::cout << " "; }
        std::cout << i + 1 << " " << char(179);
        for (int j = 0; j < size; j++) {
            if (Player[i][j].hit == Indefinitely) {
                std::cout << "  ";
            } else {
                std::cout << Player[i][j].hit << " ";
            }
        }
        std::cout << char(179);
        std::cout << std::endl;
    }
    std::cout << "   ";
    for (int i = 0; i < 22; i++) {
        if (i == 0) {
            std::cout << char(192);
        } else if (i == 21) {
            std::cout << char(217);
        } else {
            std::cout << char(196);
        }
    }
    std::cout << std::endl;
}

void Print_Sea_Battlw_for_Player(Cell **&Player, size_t size) {
    std::cout << "      Player field!\n";
    std::cout << "    ";
    for (int i = 0; i < size; i++) {
        std::cout << i + 1 << " ";
    }
    std::cout << std::endl;
    std::cout << "   ";
    for (int i = 0; i < 22; i++) {
        if (i == 0) {
            std::cout << char(218);
        } else if (i == 21) {
            std::cout << char(191);
        } else {
            std::cout << char(196);
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < size; i++) {
        if (i != size - 1) { std::cout << " "; }
        std::cout << i + 1 << " " << char(179);
        for (int j = 0; j < size; j++) {
            if (Player[i][j].Ship_ID != 0) {
                std::cout << Player[i][j].Ship_ID << " ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << char(179);
        std::cout << std::endl;
    }
    std::cout << "   ";
    for (int i = 0; i < 22; i++) {
        if (i == 0) {
            std::cout << char(192);
        } else if (i == 21) {
            std::cout << char(217);
        } else {
            std::cout << char(196);
        }
    }
    std::cout << std::endl;
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
    random_placement_of_ships(pc, size);
    random_placement_of_ships(player, size);
    Print_Sea_Battlw_for_PC(pc, size);
    Print_Sea_Battlw_for_Player(player, size);
}

