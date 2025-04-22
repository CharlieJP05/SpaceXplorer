#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>


void create_map(int x, int y, char map[x][y]) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            /*if (map[i][j] == ' ') {
                continue;
            }*/
            int r = rand() % (100+1);
            if (r < 90) {
                map[i][j] = 'X';
            } else if (r < 95) {
                map[i][j] = '0';
            } else if (r < 100) {
                map[i][j] = 'S';
            } else {
                map[i][j] = 219;
            }
        }
    }
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (map[i][j] == '0') {
                int r = rand() % (4);

                if (r == r && i + 2 < x) {
                    map[i+1][j] = '|';
                    map[i+2][j] = '|';
                }

                //if (r == 1 && j + 2 < y) map[i][j+1] = '-'; map[i][j+2] = '-';
                //if (r == 2 && i - 1 >=0) map[i-1][j] = '|'; map[i-1][j] = '|';
                //if (r == 3 && j - 2 >=0) map[i][j-1] = '-'; map[i][j-2] = '-';
            }
        }
    }
}

void display_map(int x, int y, char map[x][y]) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%c  ", map[i][j]);
        }
        printf("\n");
    }
}

main(void) {
    srand((unsigned)time(NULL));
    int x = 20, y = 20;
    char map[x][y];
    create_map(x, y, map);
    display_map(x, y, map);
    return 0;
}