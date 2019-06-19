#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define ESC 27

#define SNACK_COLOR 15
#define FOOD_COLOR 10
#define BG_COLOR 0
#define WALL_COLOR 55
#define TEXT_COLOR 10

#define TRUE 1
#define FALSE 0

#define FINAL_SNACK_SPEED 100 //Max speed of snack

struct snack
{
	int x, y; //coordinates of the snake
	struct snack * next;
};

int score = 0;
int food_position[2];//Food location

int max_score = 0;

void gotoxy(int x, int y)    //Set the output coordinates in bytes

{
        COORD pos;
        pos.X = x;
        pos.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void set_color(int b)         //color function
{
    HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE)) ;
    SetConsoleTextAttribute(hConsole,b) ;
}

//function displays the walls
void show_wall()
{
    //Sucker to draw the wall method (purely think that the cycle is too much trouble, this as long as the copy like)
    int a[20][30] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    };
    set_color(WALL_COLOR);
    int i, j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j< 30; j++)
        {
            if (a[i][j] == 1)
            {
                set_color(WALL_COLOR);
                printf("*");
            }
            else
            {
                set_color(BG_COLOR);
                printf("  ");
            }
        }
        printf("\n");
    }
    set_color(TEXT_COLOR);
    gotoxy(62, 3);
    printf("Made By:ra921741");
    gotoxy(62, 5);
    printf("Enjoy the game:");
    set_color(TEXT_COLOR);
    gotoxy(62, 7);
	printf("Use 'w', 'a', 's', 'd' to move");
	gotoxy(62, 9);
	printf("Press the ESC key to exit");
	gotoxy(62, 11);
	printf("Current Score: ");
	gotoxy(62, 13);
	printf("The highest score:  %d", max_score);

}

//Production of  food
void make_food(struct snack * mySnack)
{
    srand(clock());
    int x = rand()%52+1; //Because the x-coordinate of the rightmost wall here is 58
    int y = rand()%17+1; //Because the bottom of the wall has a y coordinate of 19
    food_position[0] = x % 2?x+1:x;//Make sure that the x direction is even
    food_position[1] = y;
    struct snack * p = mySnack;
    while(p != NULL)
    {
        if (food_position[0] == p->x || food_position[1] == y)//If the snake coincides with the re-generated food
        {
            x = rand()%57+1;
            y = rand()%17+1;
            food_position[0] = x % 2?x+1:x;// x direction is even
            food_position[1] = y;
            struct snack * p = mySnack;
            p = mySnack;
        }
        p = p->next;
    }
    set_color(FOOD_COLOR);
    gotoxy(food_position[0], food_position[1]);
    printf("*");
}

//food, if you return to TRUE
int isEat(struct snack * mySnack)
{
    int flag = FALSE;
    if (mySnack->x == food_position[0] && food_position[1] == mySnack->y)
    {
        flag = TRUE;
    }
    return flag;
}

//initializes the interface
void init(struct snack * mySnack)
{
	show_wall();
	make_food(mySnack);
	draw_Snack(mySnack);
}

//if the snake hits the wall
int hitWall(struct snack * mySnack)
{
    int flag = FALSE;
    if (mySnack->y<1 || mySnack->y>19 || mySnack->x<2 || mySnack->x>58)
    	flag = TRUE;
    return flag;
}

//if the snake hits itself
int hitSelf(struct snack * mySnack)
{
    int flag = FALSE;
    struct snack * p = mySnack->next;
    while(p != NULL)
    {
        if (p->x == mySnack->x && p->y == mySnack->y)
            flag = TRUE;
        p = p->next;
    }
    return flag;
}

//snake drawing
void draw_Snack(struct snack * mySnack)
{
	set_color(SNACK_COLOR);
	struct snack * p = mySnack;
	gotoxy(p->x, p->y);
	printf("i");
	p = p->next;
	if (p != NULL)
    {
        while (p != NULL)
        {
            gotoxy(p->x, p->y);
            printf("*");
            p = p->next;
        }

    }
}

int main(void)
{
	system("mode con cols=100 lines=25");//Setting the console window size
	int direct = UP;
	int key = 0;
	int delay_time = 500;
	int choice;
	struct snack * mySnack = (struct snack *)malloc(sizeof(struct snack));
	mySnack->x = 30;
	mySnack->y = 10;
	mySnack->next = NULL;

	struct snack * p;
	struct snack * tail; //save the last node
	struct snack * perTail; //Previous node for saving the last node

	FILE * fp = fopen("record.txt", "a+");  //highest record file

	if (fp == NULL)
	{
		printf("History File not found!");
		exit(-1);
	}
	char sc[8];

	if (fgets(sc, 8, fp) != NULL)
		max_score = atoi(sc);

	init(mySnack);
	while (1)
	{
		if (kbhit())
		{
			key = getch();
			switch (key)
			{
			case 'w':
			case 'W':
				if (direct != DOWN)
				{
					direct = UP;
				}
				break;
			case 's':
			case 'S':
				if (direct != UP)
				{
					direct = DOWN;
				}
				break;
			case 'a':
			case 'A':
				if (direct != RIGHT)
				{
					direct = LEFT;
				}
				break;
			case 'd':
			case 'D':
				if (direct != LEFT)
				{
					direct = RIGHT;
				}
				break;
			case ESC:
				choice = MessageBox(NULL,TEXT("Want to Exit?"),TEXT("Warning!"),MB_ICONINFORMATION|MB_YESNO);
				switch (choice){
				case IDYES:
					if (score > max_score)
					{
						fclose(fp);
						fp = fopen("record.txt", "w");
						if(fp == NULL)
						{
							printf("History file not found!");
							exit(-1);
						}
						fprintf(fp, "%d", score);
						fclose(fp);
					}
						exit(0);
						break;
				case IDNO:
						break;
				}
			}
		}

        p = (struct snack *)malloc(sizeof(struct snack));  //Generate a new node

		if (direct == UP)
        {
            p->y = (mySnack->y)-1;
            p->x = mySnack->x;
        }
		else if(direct == DOWN)
        {
            p->y = mySnack->y+1;
            p->x = mySnack->x;
        }
		else if(direct == LEFT)
        {
            p->x = mySnack->x-2;
            p->y = mySnack->y;
        }
		else
        {
            p->x = mySnack->x +2;
            p->y = mySnack->y;
        }
        p->next = mySnack;
        mySnack = p;

        if (isEat(mySnack)) //regenarate the food
        {
        	score++;
        	if (delay_time > FINAL_SNACK_SPEED)
        		delay_time -= 50;
        	set_color(TEXT_COLOR);
        	gotoxy(62, 11);
			printf("Current Score:  %d", score);
            make_food(mySnack); //generated new food
        }
        else
        {
            tail = mySnack;
            perTail = NULL;
            while (tail->next != NULL)
            {
                perTail = tail;
                tail = tail->next;
            }
            set_color(BG_COLOR);
            gotoxy(tail->x, tail->y);
            printf("*");
            free(tail);
            perTail->next = NULL; //Pointing the tail node to NULL
        }

		if (hitWall(mySnack) || hitSelf(mySnack))
		{
			//Game Over
			if (score > max_score)
			{
				fclose(fp);
				fp = fopen("record.txt", "w");
				if(fp == NULL)
				{
					printf("Log file not Found!");
					exit(-1);
				}
				fprintf(fp, "%d", score);
				fclose(fp);
			}
			MessageBox(NULL,TEXT("Please Come Back and play again!"),TEXT("Sorry!"),MB_OK);
			exit(0);
		}
		draw_Snack(mySnack);
		Sleep(delay_time);
	}

	return 0;
}
