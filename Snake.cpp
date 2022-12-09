#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <locale.h>

using namespace std;
bool gameOver;
const int height = 20 + 2;
const int width = 20 + 2;
int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100];
int nTail;
WINDOW *board_win;
WINDOW *score_win;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
void setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruit_x = rand() % (width - 2) + 1; // rand 1-20 
	fruit_y = rand() % (height - 2) + 1;
	score = 0;
}

void drawBorder()
{
    box(board_win, 0, 0);
	wrefresh(board_win);
}

void drawScoreBorder()
{
	box(score_win, 0, 0);
	mvwprintw(score_win, 0, 2, "score");
	wrefresh(score_win);
}

void init_board()
{
	int xMax, yMax;
	getmaxyx(stdscr, yMax, xMax);
    board_win = newwin(height, width, 0, 0);
	score_win = newwin(5, 9, 0, 25);
	drawBorder();
	drawScoreBorder();
}



void drawScore()
{
	werase(score_win);
	drawScoreBorder();
	mvwprintw(score_win, 2, 4, "%d", score);
	wrefresh(score_win);

}



void draw()
{
	
    werase(board_win); 
	drawBorder();

	
	// print fruit
	mvwprintw(board_win, fruit_y, fruit_x, "a"); 

	// print head
	mvwprintw(board_win, y, x, "O"); 

	// print body
	for (int i = 0; i < nTail; i++)
	{
		// mvwaddch(board_win, tail_y[i], tail_x[i], 'o'); 
		mvwprintw(board_win, tail_y[i], tail_x[i], "o");
	}

    // for (int i = 1; i < height + 1; i++)
	// {
	// 	for (int j = 1; j < width + 1; j++)
	// 	{
	// 		if (i == y && j == x)
	// 		{
	// 			mvwprintw(board_win, y, x, "•");
	// 		}
	// 	}
	// }


	
	wrefresh(board_win);

	
}





void draw_gameover()
{
	printw("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n");
	printw("███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀\n");
	printw("██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼\n");
	printw("██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀\n");
	printw("██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼\n");
	printw("███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄\n");
	printw("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n");

	printw("███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼\n");
	printw("██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼\n");
	printw("██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼\n");
	printw("██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼\n");
	printw("███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄\n");
	printw("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n");

	printw("Score: %d", score);
	refresh();
}

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) 
    {
        ungetch(ch);
        return 1;
    } 
    else 
    {
        return 0;
    }
}

int getch_noblock() {
    if (kbhit())
        return getch();
    else
        return -1;
}

void input()
{
	if (kbhit())
	{
		switch (getch_noblock())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'q':
			gameOver = true;
			break;
		}
	}
}
void logic()
{
	int prev_x = tail_x[0];
	int prev_y = tail_y[0];
	int prev_2x, prev_2y;
	tail_x[0] = x;
	tail_y[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev_2x = tail_x[i];
		prev_2y = tail_y[i];
		tail_x[i] = prev_x;
		tail_y[i] = prev_y;
		prev_x = prev_2x;
		prev_y = prev_2y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width - 2 || x < 1 || y > height - 2 || y < 1)
	{
		gameOver = true;
	}

	for (int i = 0; i < nTail; i++)
		if (tail_x[i] == x && tail_y[i] == y)
			gameOver = true;

	if (x == fruit_x && y == fruit_y)
	{
		score += 1;
		drawScore();
		fruit_x = rand() % (width - 2) + 1;
		fruit_y = rand() % (height - 2) + 1;
		nTail++;
	}
}



int main(int argc, char const *argv[])
{
	int gameSpeed = 0;
	if (argc == 1)
	{
		gameSpeed = 300;
	}
	else if (argc == 2)
	{
		if (strcmp(argv[1], "easy") == 0)
		{
			gameSpeed = 500;
		}
		else if (strcmp(argv[1], "medium") == 0)
		{
			gameSpeed = 300;
		}
		else if (strcmp(argv[1], "hard") == 0)
		{
			gameSpeed = 100;
		}
		
	}
	
	srand(time(NULL));
	initscr();
    noecho();
	curs_set(0);
	
	setup();
	init_board();
	
	while (!gameOver)
	{
		draw();
		input();
		logic();
		timeout(gameSpeed);
		usleep(2000);
	}
	
	

	endwin();

	return 0;
}
