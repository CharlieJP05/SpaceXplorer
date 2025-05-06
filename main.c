#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "funcs.c"


int main(void) {
    srand((unsigned)time(NULL)); // allows for random to be used
    hide_cursor(); // hide cursor
    Map map;
    init_map(&map,18); // init map
    char prbuff[2048] = {0};
    create_map(&map); // create map
    //display_map(&map,"None"); // show map
    spawn_asteroid(&map);
    update(&map, prbuff, 0);
    for (int i = 0; i < 1000; i++) {//main loop
        //Input
        printf("Action: \n");
        char input = 0;

        while (1) {
            if (_kbhit()) {
                input = _getch(); // get input without Enter
                break;
            } else {

                display_map(&map, prbuff);
            }
            Sleep(10); // delay for game pacing
        }

        // Time
        Sleep(100); // delay for game pacing

        // Logic
        spawn_asteroid(&map);
        update(&map, prbuff, input); // input might be 0 if timeout

        // Draw funcs
        display_map(&map, prbuff);

        // Clear buffer
        memset(prbuff, 0, sizeof(prbuff));
    }
    return 0;
}