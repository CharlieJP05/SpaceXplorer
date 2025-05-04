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

void init_map(Map *map,int worldSize) {
    worldSize = 18; // overwrite value
    map->worldSize = worldSize;
    for (int i = 0; i < map->worldSize; i++) {
        for (int j = 0; j < map->worldSize; j++) {
            map->world[i][j].contains = 0;
            map->world[i][j].symbol = ' ';
            map->world[i][j].asteroid.symbol = '#';
            map->world[i][j].asteroid.direction = 5;
            map->world[i][j].scrap.symbol = 'X';
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
            } else if (r < 95&&0) { // disabled
                int a = rand() % (4);
                map->world[i][j].contains = 1; // asteroid // disabled
                map->world[i][j].asteroid.direction = a;
            } else if (r < 100) {
                map->world[i][j].contains = 2; // scrap
            } else {
                map->world[i][j].contains = 3; // player character, currently just a small chance it shows, to test display
            }
        }
    }
}

void display_map(Map *map,char prbuff[]) {
    int x = map->worldSize;
    int y = map->worldSize;
    system("cls");
    char buffer[2048] = {0};
    strcat(buffer,"================================================================================\n");
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
            }
            temp[1] = '\0';               // Null terminate
            strcat(buffer, temp);// print with type character
            strcat(buffer," ");
        }
        strcat(buffer,"||              ||\n"); // new line at end of line
    }
    strcat(buffer,"================================================================================\n");
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
                printf("pos:bottom -> %d:%d\n",pos,y);
                map->world[pos][y-1].asteroid.direction = dir;
                map->world[pos][y-1].contains = 1;
            } else { // asteroid should spawn from the top
                printf("pos:top -> %d:%d\n",pos,0);
                map->world[pos][0].asteroid.direction = dir;
                map->world[pos][0].contains = 1;
            }
        } else {
            int pos = rand() % (x);
            if (dir == 1) {// asteroid should spawn from the left
                printf("left:pos -> %d:%d\n",0,pos);
                map->world[0][pos].asteroid.direction = dir;
                map->world[0][pos].contains = 1;
            } else {// asteroid should spawn from the right
                printf("right:pos -> %d:%d\n",x,pos);
                map->world[x-1][pos].asteroid.direction = dir;
                map->world[x-1][pos].contains = 1;
            }
        }
    }

}

void move_asteroid(Map *map,char prbuff[]) {
    Map tempMap;
    memcpy(&tempMap,map,sizeof(Map));
    int x = map->worldSize;
    int y = map->worldSize;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            switch (tempMap.world[i][j].contains) {
                case 0://null
                    break;
                case 1://asteroid
                    switch (map->world[i][j].asteroid.direction) { // select from asteroid directions
                        case 0:
                            map->world[i][j].contains = 0;
                            map->world[i][j].asteroid.direction = 5;
                        if (j-1 >= 0){
                            map->world[i][j-1].contains = 1;
                            map->world[i][j-1].asteroid.direction = 0;
                        } else {

                        }
                        break;
                        case 1:
                            map->world[i][j].contains = 0;
                            map->world[i][j].asteroid.direction = 5;
                        if (i+1 < x){
                            map->world[i+1][j].contains = 1;
                            map->world[i+1][j].asteroid.direction = 1;
                        } else {

                        }
                        break;
                        case 2:
                            map->world[i][j].contains = 0;
                            map->world[i][j].asteroid.direction = 5;
                        if (j+1 < y){
                            map->world[i][j+1].contains = 1;
                            map->world[i][j+1].asteroid.direction = 2;
                        } else {

                        }
                        break;
                        case 3:
                            map->world[i][j].contains = 0;
                            map->world[i][j].asteroid.direction = 5;
                        if (i-1 >= 0){
                            map->world[i-1][j].contains = 1;
                            map->world[i-1][j].asteroid.direction = 3;
                        } else {

                        }
                        break;
                    }
                break;
                case 2://scrap

                break;
                case 3://player

                break;
            }
        }
    }
}