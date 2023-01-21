#include <iostream>
#include <random>


enum Hit_Status {
    Indefinitely,
    Hit = 1,
    Miss = -1
//    Terminated = 3
};
struct Cell {
    Hit_Status hit;
    int Ship_ID;
};

void Print_Sea_Battlw_for_PC(Cell **&Player, size_t size);

void Print_Sea_Battlw_for_Player(Cell **&Player, size_t size);


bool ship(Cell **&Player, int x, int y, int a, int b) {

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
    } else if (x == a) {
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
            if ((x + ship_size) < size && ship(Player, x, y, x + ship_size, y)) {
                for (int c = x; c < (x + ship_size); c++) {
                    Player[c][y].Ship_ID = ship_size;
                }
            } else if ((y + ship_size < size) && ship(Player, x, y, x, y + ship_size)) {
                for (int c = y; c < (y + ship_size); c++) {
                    Player[x][c].Ship_ID = ship_size;
                }
            } else if ((y - ship_size > 0) && ship(Player, x, y, x, y - ship_size)) {
                for (int c = y - ship_size; c < y; c++) {
                    Player[x][c].Ship_ID = ship_size;
                }
            } else if ((x - ship_size > 0) && ship(Player, x, y, x - ship_size, y)) {
                for (int c = x - ship_size; c < x; c++) {
                    Player[c][y].Ship_ID = ship_size;
                }
            } else {
                std::cout << "not";
                i--;
            }
        }
        count_of_ships++;
        ship_size--;
    }
}

void manual_placement(Cell **&Player, size_t size) {

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

void Computer_Shot_Repeat(Cell **&Player, size_t size, int x, int y) {
    if ((x + 1) < size && Player[x + 1][y].hit == Indefinitely) {
        Player[x + 1][y].hit = Hit;
        Computer_Shot_Repeat(Player, size, x + 1, y);
    } else if ((y + 1) < size && Player[x][y + 1].hit == Indefinitely) {
        Player[x][y + 1].hit = Hit;
        Computer_Shot_Repeat(Player, size, x, y + 1);
    } else if ((x - 1) > 0 && Player[x - 1][y].hit == Indefinitely) {
        Player[x - 1][y].hit = Hit;
        Computer_Shot_Repeat(Player, size, x - 1, y);
    } else if ((y - 1) > 0 && Player[x][y - 1].hit == Indefinitely) {
        Player[x][y - 1].hit = Hit;
        Computer_Shot_Repeat(Player, size, x, y - 1);
    } else {
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
        Computer_Shot_Repeat(Player, size, x, y);
    } else {
        Player[x][y].hit = Miss;
    }
}

void Computer_Shot_Random(Cell **&Player, size_t size) {
    std::random_device rand;
    int x, y;
    do {
        std::uniform_int_distribution<int> disribution(0, 9);
        x = disribution(rand);
        y = disribution(rand);
    } while (Player[x][y].Ship_ID != 0);
    if (Player[x][y].Ship_ID != 0) {
        Player[x][y].hit = Hit;
        Computer_Shot_Random(Player, size);
    } else {
        Player[x][y].hit = Miss;
    }
}

void (*Computer[2])(Cell **&Player, size_t size){Computer_Shot_Random, Computer_Shot};

void (*placement[2])(Cell **&Player, size_t size){random_placement_of_ships, manual_placement};

bool Win_Game(Cell **&Player, size_t size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (Player[i][j].Ship_ID != 0 && Player[i][j].hit != Hit) {
                return false;
            }
        }
    }
    return true;
}

void Human_Computer(Cell **&Player, size_t size, Cell **&PC) {
    for (int i = 0; i < size; i++) {
        Player[i] = new Cell[size]{Indefinitely, 0};
    }
    for (int i = 0; i < size; i++) {
        PC[i] = new Cell[size]{Indefinitely, 0};
    }
    char arrangement;
    std::cout << "The computer arranges for the player - a\n"
                 "The player places manually -R\n";
    std::cin >> arrangement;
    placement[arrangement](Player, size);
    random_placement_of_ships(PC, size);
    int difficulty;
    std::cout << "Select computer difficulty:\n"
                 "0- Random shot\n"
                 "1 - Intellectual game.";
    std::cin >> difficulty;
    int count = 0;
    do {

        Print_Sea_Battlw_for_PC(PC, size);
        Print_Sea_Battlw_for_Player(Player, size);
        Player_Turn(PC, size);
        if (count >= 20) {
            if(Win_Game(PC, size)){
                std::cout<<"Player win!!!";
                return;
            }
        }
        Computer[difficulty](Player, size);
        if (count >= 20) {
            if(Win_Game(Player, size)){
                std::cout<<"Pc win!!!";
                return;
            }
        }
        count++;
    } while ();

}

void Computer_Сomputer(Cell **&Player, size_t size, Cell **&PC) {

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
            if (Player[i][j].hit == Miss) {
                std::cout << "*" << " ";
            } else if (Player[i][j].hit == Hit) {
                std::cout << "X" << " ";
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
            if (Player[i][j].hit == Hit) {
                std::cout << "X" << " ";
            } else if (Player[i][j].Ship_ID != 0) {
                std::cout << "#" << " ";
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
    Cell **pc = new Cell *[size];
    char modeSelection;
    std::cout << "Game modes:\n"
                 "h: human - computer;\n"
                 "c: Computer - computer;\n"
                 "e: End game";
    std::cin >> modeSelection;
    switch (modeSelection) {
        case 'h':
            Human_Computer(player, size, pc);
            break;
        case 'c':
            Computer_Сomputer(player, size, pc);
            break;
        case 'e':
            break;
    }

    return 0;
}

