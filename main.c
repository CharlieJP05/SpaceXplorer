#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
//#include "funcs.h"
#include "funcs.c"
//#include "structs.h"
#include "structs.c"


int main(void) {
    srand((unsigned)time(NULL)); // allows for random to be used
    hide_cursor(); // hide cursor
    Map map;
    init_map(&map,18); // init map
    char prbuff[2048] = {0};
    create_map(&map); // create map
    int print = 0;
    display_map(&map,"None",1); // show map
    spawn_asteroid(&map);
    for (int i = 0; i < 1000; i++) {//main loop
        //Input
        char input = 0;
        while (_kbhit()) {
            _getch(); // Consume any lingering input
        }

        while (1) {
            if (_kbhit()) {
                input = _getch(); // get input without Enter
                break;
            } else {
                Sleep(10);
                if (time(NULL) % 2 == 0) {
                    display_map(&map,prbuff,0);
                } else {
                    display_map(&map,prbuff,1);
                }
                memset(prbuff, 0, sizeof(prbuff));

            }
        }

        // Logic
        spawn_asteroid(&map);
        move(&map, prbuff, input);
        check_collision(&map);

        // Draw funcs
        display_map(&map, prbuff,1);

        // Clear buffer
        memset(prbuff, 0, sizeof(prbuff));
        Sleep(100);
    }
    return 0;
}