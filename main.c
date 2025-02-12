#include <ncurses.h> // Add compilation option -lncurses
#include <stdio.h>

void main() {

    // ---------------------------------------
    // INITIALISATION
    // à n'appeler qu'une fois au début du main
    initscr();          // Initialize ncurses
    cbreak();           // Disable line buffering
    noecho();           // Don't echo keyboard input
    nodelay(stdscr, TRUE);  // Enable non-blocking mode
    // ---------------------------------------
    
    int x = 5;
    int y = 5;
    while(1) {  // Boucle infinie

        char ch = getch(); // Récupère la touche appuyée
        if (ch == 'd'){
            y += 1;
        } else if (ch == 'q'){
            y -= 1;
        } else if (ch == 'z'){
            x -= 1;
        } else if (ch == 's'){
            x += 1;
        }

        mvprintw(x, y, "X");  // Affiche X à la ligne x et à la colonne y
        curs_set(0);          // Empeche l'affichage du curseur
        refresh();            // Rafraichit le terminal
    }
    
    // ---------------------------------------
    // FIN
    // Laisser ça à la fin du main
    endwin();           // Cleanup
    // ---------------------------------------
}

    
