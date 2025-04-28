#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>


void create_map(int x, int y, char map[x][y]) {
    for (int i = 0; i < x; i++) { // iterate though x and y of map
        for (int j = 0; j < y; j++) {
            /*if (map[i][j] == ' ') {
                continue;
            }*/
            int r = rand() % (100+1); // choose what each space should be - will be replaced with spawning later
            if (r < 90) {
                map[i][j] = ' ';
            } else if (r < 95) {
                map[i][j] = '0';
            } else if (r < 100) {
                map[i][j] = 'X';
            } else {
                map[i][j] = 219; // player character, currently just a small chance it shows, to test display
            }
        }
    }
}

void display_map(int x, int y, char map[x][y]) {
    for (int i = 0; i < x; i++) { // iterate through
        for (int j = 0; j < y; j++) {
            printf("%c  ", map[i][j]); // print with type character
        }
        printf("\n"); // new line at end of line
    }
}

main(void) {
    srand((unsigned)time(NULL)); // allows for random to be used
    int x = 20, y = 20; // map size
    char map[x][y]; // map
    create_map(x, y, map); // create map
    display_map(x, y, map); // show map
    return 0;
}