#include <ncurses.h>

#include "board.hpp"

#define BOARD_DIM 18
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2.5

int main(int argc, char const *argv[])
{
    initscr();
    refresh();

    Board(BOARD_ROWS, BOARD_COLS);
    
    getch();
    endwin();
    return 0;
}
