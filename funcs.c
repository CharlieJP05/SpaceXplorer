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
#define CLEAR 6

void init_map(Map *map,int worldSize) {
    const char gear[] = "\xE2\x9A\x99";

    worldSize = 18; // overwrite value
    map->worldSize = worldSize;
    for (int i = 0; i < map->worldSize; i++) {
        for (int j = 0; j < map->worldSize; j++) {
            map->world[i][j].contains = 0;
            map->world[i][j].symbol = ' ';
            map->world[i][j].asteroid.symbol = '#';
            map->world[i][j].asteroid.direction = 5;
            map->world[i][j].scrap.symbol = 'X';
            //map->world[i][j].scrap.symbol = gear; - cant use, not char, char*
            map->world[i][j].player.symbol = 219;
            map->world[i][j].player.lives = 5;
            map->world[i][j].player.scrap = 0;
        }
    }
}

void create_map(Map *map) {
    int x = map->worldSize;
    int y = map->worldSize;
    for (int i = 0; i < x; i++) { // iterate though x and y of map x = i y = j
        for (int j = 0; j < y; j++) {
            int r = rand() % (100+1); // choose what each space should be to start
            //int r = 50;
            if (r < 90) {

                map->world[i][j].contains = 0; // empty
            } else if (r < 95) { // disabled
                int a = rand() % (4);
                map->world[i][j].contains = 1; // asteroid // disabled
                map->world[i][j].asteroid.direction = a;
            } else {
                map->world[i][j].contains = 2; // scrap
            }
        }
    }
    map->world[x/2][y/2].contains = 3; // player
}

void display_map(Map *map,char prbuff[]) {
    //clear_screen();
    move_cursor_top_left();
    //system("cls");
    int x = map->worldSize;
    int y = map->worldSize;
    int seconds = (int)time(NULL);
    char buffer[2048] = {0};
    strcat(buffer,"||====================================||\n");
    for (int j = 0; j < y; j++) { // iterate through
        strcat(buffer,"||"); // start line
        for (int i = 0; i < x; i++) {
            char temp[2];                 // Temporary string for one char + null terminator
            switch (map->world[i][j].contains) {
                case 0:
                    temp[0] = map->world[i][j].symbol;
                break;
                case 1:
                    temp[0] = map->world[i][j].asteroid.symbol;
                break;
                case 2:
                    temp[0] = map->world[i][j].scrap.symbol;
                break;
                case 3:
                    temp[0] = map->world[i][j].player.symbol;
                break;
                case 4: // or asteroid and scrap
                    if (seconds % 2 == 0) {
                        temp[0] = map->world[i][j].asteroid.symbol;
                    } else {
                        temp[0] = map->world[i][j].scrap.symbol;
                    }
                break;
            }
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
                map->world[pos][y-1].asteroid.direction = dir;
                map->world[pos][y-1].contains = 1;
            } else { // asteroid should spawn from the top
                map->world[pos][0].asteroid.direction = dir;
                map->world[pos][0].contains = 1;
            }
        } else {
            int pos = rand() % (x);
            if (dir == 1) {// asteroid should spawn from the left
                map->world[0][pos].asteroid.direction = dir;
                map->world[0][pos].contains = 1;
            } else {// asteroid should spawn from the right
                map->world[x-1][pos].asteroid.direction = dir;
                map->world[x-1][pos].contains = 1;
            }
        }
    }

}

int check_collision(Map *map, int i, int j) {
    int x = map->worldSize;
    int y = map->worldSize;
    switch (map->world[i][j].contains) {
        case 0:
            return 1; // sets to asteroid
        break;
        case 1:
            return 1; // sets to asteroid -- add logic to do asteroid on asteroid collision TODO
        break;
        case 2:
            return 4; // sets to asteroid and scrap
        break;
        case 3:
            return 5; // sets to player/asteorid
        break;
        case 4:
            return 4; // sets to asteroid and scrap
        break;
        default:
            return 1; // sets to asteroid
    }
}

void update(Map *map,char prbuff[],char action) {
    Map tempMap;
    memcpy(&tempMap,map,sizeof(Map));
    int x = map->worldSize;
    int y = map->worldSize;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            int c = 0; // set asteroid
            switch (tempMap.world[i][j].contains) {
                case 0://null
                    break;
                case 4://asteroid
                    c = 2; // set scrap
                    case 1: // or asteroid and scrap
                    switch (map->world[i][j].asteroid.direction) { // select from asteroid directions
                        case 0:
                            map->world[i][j].contains = c; // allows it to move over scrap
                            map->world[i][j].asteroid.direction = CLEAR;
                        if (j-1 >= 0){
                            map->world[i][j-1].contains = check_collision(map,(i),(j-1));
                            map->world[i][j-1].asteroid.direction = 0;
                            map->world[i][j-1].asteroid.symbol = '^';
                        } else {

                        }
                        break;
                        case 1:
                            map->world[i][j].contains = c;
                            map->world[i][j].asteroid.direction = CLEAR;
                        if (i+1 < x){
                            map->world[i+1][j].contains = check_collision(map,(i+1),(j));
                            map->world[i+1][j].asteroid.direction = 1;
                            map->world[i+1][j].asteroid.symbol = '>';
                        } else {

                        }
                        break;
                        case 2:
                            map->world[i][j].contains = c;
                            map->world[i][j].asteroid.direction = CLEAR;
                        if (j+1 < y){
                            map->world[i][j+1].contains = check_collision(map,(i),(j+1));
                            map->world[i][j+1].asteroid.direction = 2;
                            map->world[i][j+1].asteroid.symbol = 'v';
                        } else {

                        }
                        break;
                        case 3:
                            map->world[i][j].contains = c;
                            map->world[i][j].asteroid.direction = CLEAR;
                        if (i-1 >= 0){
                            map->world[i-1][j].contains = check_collision(map,(i-1),(j));
                            map->world[i-1][j].asteroid.direction = 3;
                            map->world[i-1][j].asteroid.symbol = '<';
                        } else {

                        }
                        break;
                    }
                break;
                case 2://scrap

                break;
                case 3://player
                    int iTarget = 0;
                    int jTarget = 0;
                    int range = 0;
                    if (action == 'w') {
                        iTarget = i;
                        jTarget = j-1;
                        if (j-1 >=0){
                        range = 1;
                        }
                    } else if (action == 'a') { // figures out target coords and determins if in range
                        iTarget = i-1;
                        jTarget = j;
                        if (i-1 >=0){
                        range = 1;
                        }
                    } else if (action == 's') {
                        iTarget = i;
                        jTarget = j+1;
                        if (j+1 < y){
                        range = 1;
                        }
                    } else if (action == 'd') {
                        iTarget = i+1;
                        jTarget = j;
                        if (i+1 < x){
                        range = 1;
                        }
                    } else {
                    }
                    if (range) {
                        map->world[iTarget][jTarget].player = map->world[i][j].player;
                        map->world[i][j].contains = 0;
                        switch (map->world[iTarget][jTarget].contains) {
                            case 0://null
                                map->world[iTarget][jTarget].contains = 3;
                                break;
                            case 1://asteroid
                                map->world[iTarget][jTarget].contains = 3;
                                map->world[iTarget][jTarget].player.lives--;
                                break;
                            case 2://scrap
                                map->world[iTarget][jTarget].contains = 3;
                                map->world[iTarget][jTarget].player.scrap++;
                                break;
                            case 3://player
                                // fucntion for future if multiple ships are on map
                                break;
                            case 4://asteroid and scrap
                                map->world[iTarget][jTarget].contains = 3;
                                map->world[iTarget][jTarget].player.scrap++;
                                map->world[iTarget][jTarget].player.lives--;
                                break;
                        }
                    }

                break;
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