#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>


void create_map(int x, int y, char map[x][y]) {
    for (int i = 0; i < x; i++) { // iterate though x and y of map x = i y = j
        for (int j = 0; j < y; j++) {
            /*if (map[i][j] == ' ') {
                continue;
            }*/
            int r = rand() % (100+1); // choose what each space should be - will be replaced with spawning later
            if (r < 90) {

                map[i][j] = ' ';
            } else if (r < 95&&0) {// unsued as of now as no asteroid spawn on startup, may be removed
                int a = rand() % (4);
                if (a==0) {
                    map[i][j] = 'i';
                } else if (a==1) {
                    map[i][j] = 'l';
                } else if (a==2) {
                    map[i][j] = 'k';
                } else {
                    map[i][j] = 'j';
                }
            } else if (r < 100) {
                map[i][j] = "X"; // ⚙
            } else {
                map[i][j] = 219; // player character, currently just a small chance it shows, to test display
            }
        }
    }
}

void display_map(int x, int y, char map[x][y],char prbuff[]) {
    system("cls");
    char buffer[2048] = {0};
    strcat(buffer,"================================================================================\n");
    for (int j = 0; j < y; j++) { // iterate through
        strcat(buffer,"||"); // start line
        for (int i = 0; i < x; i++) {
            char temp[2];                 // Temporary string for one char + null terminator
            temp[0] = map[i][j];          // Assign the character
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

void spawn_asteroid(int x, int y, char map[x][y]) {
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
                map[pos][y-1] = 'i';
            } else { // asteroid should spawn from the top
                printf("pos:top -> %d:%d\n",pos,0);
                map[pos][0] = 'k';
            }
        } else {
            int pos = rand() % (x);
            if (dir == 1) {// asteroid should spawn from the left
                printf("left:pos -> %d:%d\n",0,pos);
                map[0][pos] = 'l';
            } else {// asteroid should spawn from the right
                printf("right:pos -> %d:%d\n",x,pos);
                map[x-1][pos] = 'j';
            }
        }
    }

}

void move_asteroid(int x, int y, char map[x][y],char prbuff[]) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            switch (map[i][j]) { // select from asteroid directions
                case 'i':
                    map[i][j] = ' ';
                    if (j-1 >= 0){
                        map[i][j-1] = 't';
                    } else {

                    }
                break;
                case 'l':
                    map[i][j] = ' ';
                    if (i+1 < x){
                        map[i+1][j] = 'h';
                    } else {

                    }
                break;
                case 'k':
                    map[i][j] = ' ';
                    if (j+1 < y){
                        map[i][j+1] = 'g';
                    } else {

                    }
                break;
                case 'j':
                    map[i][j] = ' ';
                    if (i-1 >= 0){
                        map[i-1][j] = 'f';
                    } else {

                    }
                break;
                default:

            }
        }
    }
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            switch (map[i][j]) { // select from asteroid directions
                case 't':
                    map[i][j] = 'i';
                break;
                case 'h':
                    map[i][j] = 'l';
                break;
                case 'g':
                    map[i][j] = 'k';
                break;
                case 'f':
                    map[i][j] = 'j';
                break;
                default:

            }
        }
    }
}

void over_draw(int x, int y, char map[x][y]) {//creates player visible map layer by overdrawing map
    for (int i = 0; i < x; i++) { // Asteroid overdraw
        for (int j = 0; j < y; j++) {
            int r = 4;//4 is unused aka not asteroid
            switch (map[i][j]) { // select from asteroid directions
                case 'i':
                    r = 0;
                    map[i][j] = '0';
                    break;
                case 'l':
                    r = 1;
                    map[i][j] = '0';
                    break;
                case 'k':
                    r = 2;
                    map[i][j] = '0';
                    break;
                case 'j':
                    r = 3;
                    map[i][j] = '0';
                    break;
                default:
                    r = 4;

            }
            // ASTEROID CHECKS
                //AST = UP TAIL = DOWN
            if (r == 0 && j + 1 >= 0) { // if asteroid tail should go DOWN
                if (map[i][j+1] == ' ') {//only print if space empty
                    map[i][j+1] = '|';
                }
                if (i + 2 < x && map[i][j+2] == ' ') {//only print if space empty and if not edge
                    map[i][j+2] = '|';
                }

                //AST = RIGHT TAIL = LEFT
            } else if (r == 3 && j - 1 >=0) { // if asteroid tail should go LEFT
                if (map[i+1][j] == ' ') {//only print if space empty
                    map[i+1][j] = '-';
                }
                if (j - 2 >= 0 && map[i+2][j] == ' ') {//only print if space empty and if not edge
                    map[i+2][j] = '-';
                }
                //AST = DOWN TAIL = UP
            } else if (r == 2 && j - 1 < y) { // if asteroid tail should go UP
                if (map[i][j-1] == ' ') {//only print if space empty
                    map[i][j-1] = '|';
                }
                if (j + 2 < y && map[i][j-2] == ' ') {//only print if space empty and if not edge
                    map[i][j-2] = '|';
                }
                //AST = LEFT TAIL = RIGHT
            } else if (r == 1 && j + 1 < x) { // if asteroid tail should go RIGHT
                if (map[i-1][j] == ' ') {//only print if space empty
                    map[i-1][j] = '-';
                }
                if (j + 2 < y && map[i-2][j] == ' ') {//only print if space empty and if not edge
                    map[i-2][j] = '-';
                }
            }
            //END OF ASTEROID CHECKS
        }
    }
}

main(void) {
    srand((unsigned)time(NULL)); // allows for random to be used
    int x = 20, y = 20; // map size
    int draw = 0; //1 = DRAW VISIBILE MAP       0 = DEBUG MAP
    char map[x][y]; // map
    char visible_map[x][y];
    char prbuff[2048] = {0};
    create_map(x, y, map); // create map
    display_map(x, y, map,"None"); // show map
    spawn_asteroid(x, y, map);
    for (int i = 0; i < 1000; i++) {//main loop
        //Time
        Sleep(100);
        //Logic
        spawn_asteroid(x,y,map);
        move_asteroid(x, y, map,prbuff);
        //Draw funcs
        memcpy(visible_map, map, sizeof(map)); // copy map to visible map before overdraw
        over_draw(x, y, visible_map); // make user friendly
        if (draw == 1) {
            display_map(x, y, visible_map,prbuff);
        } else {
            display_map(x, y, map,prbuff);
        }
        memset(prbuff, 0, sizeof(prbuff));
    }
    return 0;
}