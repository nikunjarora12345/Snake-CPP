#include <iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

COORD coord = {0,0};
void gotoxy(int x, int y){
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct snake{
    int x;
    int y;
    snake* next;
}*head;

void add_snake(int x, int y){
    snake* node = new snake;
    snake* last = head;
    while(last->next != NULL)
        last = last->next;
    last->next = node;
    node->x = x;
    node->y = y;
    node->next = NULL;
}

int* remove_snake(){
    snake *temp = head;
    int xy[] = {head->x, head->y};
    head = head->next;
    delete temp;
    return xy;
}

int snake_size(){
    int counter = 0;
    snake *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
        counter ++;
    }
    return counter;
}

bool snake_collision(int x, int y){
    snake* temp = head;
    while(temp->next != NULL){
        if(temp->x == x && temp->y == y)
            return true;
        temp = temp->next;
    }
    return false;
}

int x = 20;
int dx = 1;
int y = 10;
int dy = 0;

int apple_x;
int apple_y;
bool apple_eaten = true;

int snake_length = 5;
int score = 0;

char c;
char direction = 'r';

bool running = true;

int main(){
    head = new snake;
    head->x = x;
    head->y = y;
    head->next = NULL;

    long timer = GetTickCount();
    int frames = 0;

    while(running){
        if(apple_eaten){
            srand(time(NULL));
            apple_x = rand()%79 + 1;
            apple_y = rand()%23 + 2;
            gotoxy(apple_x, apple_y);
            cout << "#";
            apple_eaten = false;
        }
        gotoxy(1,1);
        cout << "SCORE : " << score;
        gotoxy(x, y);
        cout << "*";
        gotoxy(500, 500);
        if(kbhit())
            c = getch();
        switch(c){
        case KEY_UP:
            if(direction != 'd'){
                dx = 0;
                dy = -1;
                direction = 'u';
            }
            break;
        case KEY_DOWN:
            if(direction != 'u'){
                dx = 0;
                dy = 1;
                direction = 'd';
            }
            break;
        case KEY_LEFT:
            if(direction != 'r'){
                dx = -1;
                dy = 0;
                direction = 'l';
            }
            break;
        case KEY_RIGHT:
            if(direction != 'l'){
                dx = 1;
                dy = 0;
                direction = 'r';
            }
            break;
        }

        x += dx;
        y += dy;

        add_snake(x, y);

        if(snake_size() > snake_length){
            int* xy = remove_snake();
            gotoxy(*xy, *(xy + 1));
            cout << " ";
        }

        if(snake_collision(x, y))
            running = false;

        if(x == apple_x && y == apple_y){
            apple_eaten = true;
            snake_length++;
            score += 10;
        }

        if(x > 80 || x < 0 || y > 24 || y < 0)
            running = false;

        Sleep(30);

        frames++;

        if(GetTickCount() - timer >= 1000){
            timer += 1000;
            gotoxy(35, 1);
            cout << "fps : " << frames;
            frames = 0;
        }
    }

    system("cls");
    gotoxy(30,12);
    cout << "Game Over !!!";
    gotoxy(30,13);
    cout << "Your score : " << score;
    getch();
    Sleep(2000);
    return 0;
}
