#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <time.h>

// map[0][0] = '#';                        // левый верх
// map[0][mapWidth - 1] = '#';             //правый верх
// map[mapHeight - 1][mapWidth - 1] = '#'; // правый низ
// map[mapHeight - 1][0] = '#';            // левый низ

// АСЦИЛЯТОР
// map[0][1] = '#';
// map[0][2] = '#';
// map[0][3] = '#';

// ГЛАЙДЕР
// map[1][2] = '#';
// map[2][3] = '#';
// map[3][1] = '#';
// map[3][2] = '#';
// map[3][3] = '#';

// #define mapWidth 120
// #define mapHeight 30
#define mapWidth 28
#define mapHeight 28

struct Live
{
    int x, y;
};
typedef struct Live TLive;

char map[mapHeight][mapWidth + 1];
int cellPoint[mapHeight][mapWidth + 1];
int randCell, n;

//Первое заполнение карты
void ClearMap();

//выбор метода заполнения карты
int MethodChoose(TLive p[n]);

//ручной ввод координат
void CellCord(TLive p[n]);

//генератор случайного поколения
void RandGen();

//Проверка количества живых клеток рядом
void CheckCell();

//Исключения для углов, при проверке количества живых клеток рядом
void CheckAngleUL(int i, int j);
void CheckAngleUR(int i, int j);
void CheckAngleDL(int i, int j);
void CheckAngleDR(int i, int j);

//Исключения для боковых рядов, при проверке количества живых клеток рядом
void CheckRowUP(int i, int j);
void CheckRowDW(int i, int j);
void CheckRowL(int i, int j);
void CheckRowR(int i, int j);

//Основная Проверка количества живых клеток рядом
void CheckClassic(int i, int j);

//Основные правила игры
void Cell();

//Вывод карты
void ShowMap();

//Установка курсора в левый верхний угол, чтобы окно с ума не сходило
void SetCur(int x, int y);

int main()
{
    TLive p[n];

    ClearMap();
    MethodChoose(p);
    system("CLS");

    SetCur(0, 0);
    ShowMap();
    printf("\nPress any key to see the next generation");
    printf("\nPress ESC - exit");

    SetCur(0, 0);
    do
    {
        getch();
        CheckCell();
        Cell();
        ShowMap();
        printf("\nPress any key to see the next generation");
        printf("\nPress ESC - exit");

        SetCur(0, 0);
    } while (GetKeyState(VK_ESCAPE) >= 0);

    //getch();
    return 0;
}

//ручной ввод координат
void CellCord(TLive p[n])
{
    printf("input quanity of cells: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        system("CLS");
        printf("\ninput coordinate x%d - ", i + 1);
        scanf("%d", &p[i].x);
        printf("\ninput coordinate y%d - ", i + 1);
        scanf("%d", &p[i].y);
        map[p[i].x][p[i].y] = '#';
        ShowMap();
        printf("\t\t\t\t\tpress any button");
        getch();
    }
    printf("\nresult:");
    // for (int i = 0; i < n; i++)
    // {
    //     printf("\n x%d - %d", i + 1, p[i].x);

    //     printf(" y%d - %d", i + 1, p[i].y);

    //     printf(" cell - map[%d][%d] = %c", p[i].x, p[i].y, map[p[i].x][p[i].y]);
    // }
    printf("\t\t\tpress any button");
    getch();
    system("CLS");
}

//Первое заполнение карты
void ClearMap()
{
    for (int i = 0; i < mapWidth; i++)
        map[0][i] = '.';
    map[0][mapWidth] = '\0';
    for (int j = 0; j < mapHeight; j++)
        sprintf(map[j], map[0]);
}

//Основная Проверка количества живых клеток рядом
void CheckClassic(int i, int j)
{
    if (map[i - 1][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
}

//Исключения для углов, при проверке количества живых клеток рядом
void CheckAngleUL(int i, int j)
{

    if (map[1][mapWidth - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[0][mapWidth - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[mapHeight - 1][mapWidth - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[mapHeight - 1][0] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[mapHeight - 1][1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
}
void CheckAngleUR(int i, int j)
{
    if (map[1][0] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[0][0] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[mapHeight - 1][0] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[mapHeight - 1][mapWidth - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[mapHeight - 1][mapWidth - 2] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
}
void CheckAngleDL(int i, int j)
{
    if (map[0][0] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[0][1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[mapHeight - 1][mapWidth - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[mapHeight - 2][mapWidth - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[0][mapWidth - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
}
void CheckAngleDR(int i, int j)
{
    if (map[mapHeight - 1][0] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[mapHeight - 1][1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[0][0] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[0][mapWidth - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[0][mapWidth - 2] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
}

//Исключения для боковых рядов, при проверке количества живых клеток рядом
void CheckRowUP(int i, int j)
{

    if (map[mapHeight - 1][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[mapHeight - 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[mapHeight - 1][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
}
void CheckRowDW(int i, int j)
{
    if (map[0][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[0][j] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[0][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
}
void CheckRowL(int i, int j)
{
    if (map[i - 1][mapWidth - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][mapWidth - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][mapWidth - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j + 1] == '#')
    {
        ++cellPoint[i][j];
    }
}
void CheckRowR(int i, int j)
{
    if (map[i - 1][0] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][0] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][0] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i - 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j - 1] == '#')
    {
        ++cellPoint[i][j];
    }
    if (map[i + 1][j] == '#')
    {
        ++cellPoint[i][j];
    }
}

//Проверка количества живых клеток рядом
void CheckCell()
{
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            if (i == 0 && j == 0)
            {
                CheckAngleUL(i, j);
            }
            else if (i == 0 && j == mapWidth - 1)
            {
                CheckAngleUR(i, j);
            }
            else if (i == mapHeight - 1 && j == mapWidth - 1)
            {
                CheckAngleDR(i, j);
            }
            else if (i == mapHeight - 1 && j == 0)
            {
                CheckAngleDL(i, j);
            }
            else if (i == 0)
            {
                CheckRowUP(i, j);
            }
            else if (i == mapHeight - 1)
            {
                CheckRowDW(i, j);
            }
            else if (j == 0)
            {
                CheckRowL(i, j);
            }
            else if (j == mapWidth - 1)
            {
                CheckRowR(i, j);
            }

            else
                CheckClassic(i, j);
        }
    }
}

//Основные правила игры
void Cell()
{
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {

            if (cellPoint[i][j] == 3)
            {
                map[i][j] = '#';
            }

            if (cellPoint[i][j] < 2 || cellPoint[i][j] > 3)
            {
                map[i][j] = '.';
            }
            cellPoint[i][j] = 0;
        }
    }
}

//Вывод карты
void ShowMap()
{

    map[mapHeight][mapWidth] = '\0';
    for (int j = 0; j < mapHeight; j++)
    {
        printf("%s", map[j]);
        if (j < mapHeight - 1)
        {
            printf("\n");
        }
    }
}

//Установка курсора в левый верхний угол, чтобы окно с умна не сходило
void SetCur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//генератор случайного поколения
void RandGen()
{
    srand(time(NULL));

    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            randCell = rand() % 3;
            if (randCell == 1)
                map[i][j] = '.';
            else if (randCell == 2)
                map[i][j] = '#';
            map[0][mapWidth] = '\0';
        }
    }
}

//выбор метода заполнения карты
int MethodChoose(TLive p[n])
{
    int choice;
    printf("Choosing a field filling method \nInput(1) - manual input \nInput(2) - Filling in random cells\nInput>");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("You have chosen the manual input method\nPress any button to continue");
        getch();
        system("CLS");
        CellCord(p);
    }
    else if (choice == 2)
    {
        printf("You have chosen the manual input method\nPress any button to continue");
        getch();
        system("CLS");
        RandGen();
    }
    else
    {
        printf("ERROR");
        getch();
        return 0;
    }
}
