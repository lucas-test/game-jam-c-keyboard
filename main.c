// gcc main.c -o main -lncurses -lm
#include <ncurses.h> // use -lncurses
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> // use -lm

#define LINES 20
#define COLS 20

int randint(int min, int max) {
    return min + rand() % (max - min + 1);
}

void afficher(int** tab){
    for (int i = 0; i < LINES; i ++){
        for (int j = 0; j < COLS; j ++){
            if (tab[i][j] == 0){
                mvprintw(i, j, " ");
            } else {
                mvprintw(i, j, "#");
            }
        }
        mvprintw(i, COLS, "|");
    }
}


void decaler(int** tab){
    for (int i = LINES-1; i >= 1; i --){
        for (int j = 0; j < COLS; j ++){
            tab[i][j] = tab[i-1][j];
        }
    }
    for (int j = 0; j < COLS; j ++){
        tab[0][j] = 0;
    }
    tab[0][randint(0,COLS-1)] = 1;
}


void main() {
    srand(time(NULL));
    initscr();          // Initialize ncurses
    cbreak();           // Disable line buffering
    noecho();           // Don't echo keyboard input
    nodelay(stdscr, TRUE);  // Enable non-blocking mode
    
    int** tab;
    tab = malloc(sizeof(int*)*LINES);
    for (int i = 0; i < LINES; i++){
        tab[i] = malloc(sizeof(int)*COLS);
        for (int j = 0; j < COLS; j ++){
            tab[i][j] = 0;
        }
    }

    int ch;
    int n = 0;
    int decalage_counter = 0;
    int init_time = time(NULL);
    double delta = 2000;
    while(1) {  
        // D 100
        // Q 113
        
        usleep(100);
        decalage_counter ++;
        ch = getch();
        
        if(ch != ERR) { 
            if (ch == 100){
                n ++;
                if (n >= COLS){
                    n--;
                }
            } else if (ch == 113) {
                n --;
                if (n < 0){
                    n ++;
                }
            }
            // mvprintw(0, 0, "Key pressed: %d", ch);
        }
        if (decalage_counter >= delta){
            decaler(tab);
            decalage_counter = 0;
            double elapsed_seconds = difftime(time(NULL), init_time);
            delta = 2000./log(3+elapsed_seconds);
        }
        

        afficher(tab);
        mvprintw(LINES-1, n, "X");
        mvprintw(0, COLS+1, "%.2f", delta);
        curs_set(0); 

        if (tab[LINES-1][n] == 1){
            break;
        }
        refresh();
    }
    
    endwin();           // Cleanup
    printf("%.2f\n", delta);
}

    
