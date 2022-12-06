#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <locale.h>

using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
void setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruit_x = rand() % width;
	fruit_y = rand() % height;
	score = 0;
}

void draw()
{
	erase();
	for (int i = 0; i < width+2; i++) 
    {
        printw("# "); refresh();
    }
    printw("\n"); refresh();
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				printw("# "); refresh();
			}
			if (i == y && j == x)
			{
				printw("• "); refresh();
			}
			else if (i == fruit_y && j == fruit_x)
			{
				printw(" "); refresh();
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tail_x[k] == j && tail_y[k] == i)
					{
						printw("• "); refresh();
						print = true;
					}
				}
				if (!print)
				{
					printw("  "); refresh();
				}
					
			}
				

			if (j == width - 1)
			{
				printw(" #"); refresh();
			}
			
				
		}
		printw("\n"); refresh();
	}

	for (int i = 0; i < width+2; i++)
	{
		printw("# "); refresh();
	}
	printw("\n"); refresh();
	printw("Score: %d\n", score); refresh();
}

void draw_gameover()
{
	erase();
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
	if (x > width || x < 0 || y > height || y < 0)
	{
		gameOver = true;
	}
	// if (x >= width) x = 0; else if (x < 0) x = width - 1;
	// if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tail_x[i] == x && tail_y[i] == y)
			gameOver = true;

	if (x == fruit_x && y == fruit_y)
	{
		score += 10;
		fruit_x = rand() % width;
		fruit_y = rand() % height;
		nTail++;
	}
}
int main()
{
	setup();
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	while (!gameOver)
	{
		draw();
		input();
		logic();
		usleep(2000); //sleep(10);
	}
	draw_gameover();
	return 0; 


	// draw
	// check for input
		// if no input do nothing
	// run logic even without input
}