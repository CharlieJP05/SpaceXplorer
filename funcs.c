//
// Created by charl on 04/05/2025.
//

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "funcs.h"
#include "structs.h"

void create_map(Map *map) {
    int x = map->worldSize;
    int y = map->worldSize;
    for (int i = 0; i < x; i++) { // iterate though x and y of map x = i y = j
        for (int j = 0; j < y; j++) {
            int r = rand() % (100+1); // choose what each space should be to start
            //int r = 50;
            if (r < 90) {
                //do nothing, leave empty
            } else if (r < 95) {
                int a = rand() % (4);
                add_asteroid(map,i,j,a);
            } else {
                add_scrap(map,i,j);
            }
        }
    }
    clear_space(map,x/2,y/2);
    add_player(map,x/2,y/2);
}

void display_map(Map *map,char prbuff[]) {
    //clear_screen();
    move_cursor_top_left();
    //system("cls");
    int x = map->worldSize;//TODO
    int y = map->worldSize;
    int seconds = (int)time(NULL);
    char buffer[2048] = {0};
    strcat(buffer,"||====================================||\n");
    for (int j = 0; j < y; j++) { // iterate through
        strcat(buffer,"||"); // start line
        update_symbols(map);
        for (int i = 0; i < x; i++) {
            char temp[2];                 // Temporary string for one char + null terminator
            temp[0] = get_symbol(map,i,j); // get symbol from map
            temp[1] = '\0';               // Null terminate
            strcat(buffer, temp);// print with type character
            strcat(buffer," ");
        }
        strcat(buffer,"||\n"); // new line at end of line
    }
    strcat(buffer,"||====================================||\n");
    strcat(buffer,"||");
    strcat(buffer,prbuff);
    strcat(buffer,"\n");
    printf("%s", buffer);
}

void spawn_asteroid(Map *map) {
    int x = map->worldSize;
    int y = map->worldSize;
    int asteroidChance = rand() % (100+1); // if < 90, one asteroid spawns, if >, two
    int amount = 0;
    if (asteroidChance < 90) {
        amount = 1;
    } else {
        amount = 2;
    }
    for (int i = 1; i <= amount; i++) {
        int dir = rand() % (4);
        if (dir == 0 || dir == 2) {
            int pos = rand() % (y);
            if (dir == 0) {// asteroid should spawn from the bottom
                add_asteroid(map,pos,y-1,dir);
            } else { // asteroid should spawn from the top
                add_asteroid(map,pos,0,dir);
            }
        } else {
            int pos = rand() % (x);
            if (dir == 1) {// asteroid should spawn from the left
                add_asteroid(map,0,pos,dir);
            } else {// asteroid should spawn from the right
                add_asteroid(map,x-1,pos,dir);
            }
        }
    }

}


void hide_cursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // hide cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void move_cursor_top_left() {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}