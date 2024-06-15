#include <iostream>
#include <windows.h>

using namespace std;

int HEIGHT;
int WIDTH;
HANDLE CONSOLE_COLOR = GetStdHandle(STD_OUTPUT_HANDLE);



void displayField(int **field)
{
    for (int i = 0; i < WIDTH; i++)
    {
        for(int j = 0; j < HEIGHT; j++)
        {
            if(field[i][j] == 0)
            {
                SetConsoleTextAttribute(CONSOLE_COLOR, 10);
            }
            else if(field[i][j] == 1 || field[i][j] == 3 || field[i][j] == 4)
            {
                SetConsoleTextAttribute(CONSOLE_COLOR, 12);
            }
            else
            {
                SetConsoleTextAttribute(CONSOLE_COLOR, 14);
            }
            cout << char(223) << " ";
        }
        cout << "\n";
    }
    SetConsoleTextAttribute(CONSOLE_COLOR, 15);
}


void infect(int** field, int** intervalField)
 {
    int chance;
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            srand(time(NULL));
            if ((field[i][j] == 3 || field[i][j] == 4) && (intervalField[i][j] > 1 && intervalField[i][j] < 5))
            {
                chance = rand() % 2;

                if(chance == 1)
                {
                    if (i - 1 >= 0)
                    {
                        if (field[i - 1][j] == 0)
                        {
                            field[i - 1][j] = 1;
                            intervalField[i - 1][j]++;
                        }
                    }
                    if (i + 1 < WIDTH)
                    {

                        if (field[i + 1][j] == 0)
                        {
                            field[i + 1][j] = 1;
                            intervalField[i + 1][j]++;
                        }

                    }
                    if (j - 1 >= 0)
                    {

                        if (field[i][j - 1] == 0)
                        {
                            field[i][j - 1] = 1;
                            intervalField[i][j - 1]++;
                        }
                    }
                    if (j + 1 < HEIGHT)
                    {
                        if (field[i][j + 1] == 0)
                        {
                            field[i][j + 1] = 1;
                            intervalField[i][j + 1]++;
                        }
                    }
                }

                srand(time(NULL));
                chance = rand() % 4;

                if(chance == 1)
                {
                    if(i - 1 >= 0 && j - 1 >= 0)
                    {
                        if (field[i - 1][j-1] == 0)
                        {
                            field[i - 1][j-1] = 1;
                            intervalField[i - 1][j-1]++;
                        }
                    }
                    if(i - 1 >= 0 && j + 1 < HEIGHT)
                    {
                        if (field[i - 1][j + 1] == 0)
                        {
                            field[i - 1][j + 1] = 1;
                            intervalField[i - 1][j + 1]++;
                        }
                    }
                    if(i + 1 < WIDTH && j - 1 >= 0)
                    {
                        if(field[i + 1][j - 1] == 0)
                        {
                            field[i + 1][j - 1] = 1;
                            intervalField[i + 1][j - 1]++;
                        }
                    }
                    if(i + 1 < WIDTH && j + 1 < HEIGHT)
                    {
                        if (field[i + 1][j + 1] == 0)
                        {
                            field[i + 1][j + 1] = 1;
                            intervalField[i + 1][j + 1]++;
                        }
                    }
                }

                
                if(field[i][j] != 4)
                {
                    intervalField[i][j]++;
                }
            }
            else if ((field[i][j] == 3 || field[i][j] == 1) && intervalField[i][j] >= 5)
            {
                field[i][j] = 2;
                intervalField[i][j] = 2;
            }
            else if (field[i][j] == 2 && intervalField[i][j] < 4)
            {
                intervalField[i][j]++;
            }
            else if (field[i][j] == 2 && intervalField[i][j] >= 4)
            {
                field[i][j] = 0;
                intervalField[i][j] = 1;
            }
        }
    }

    for (int i = 0; i < WIDTH; i++)
    {
        for(int j = 0; j < HEIGHT; j++)
        {
            if(field[i][j] == 1)
            {
                field[i][j] = 3;
            }
        }
    }
}

void fillField(int** field, int** intervalField, int number, int x, int y)
{

    srand(time(NULL)); 

    field[x][y] = 4;
    intervalField[x][y] = 2;

    int i = 1; 

    while (i < number) {
        int newX = x + rand() % 3 - 1;
        int newY = y + rand() % 3 - 1;

        if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT)
        {
            if (field[newX][newY] != 4 && field[newX][newY] != 3)
            {
                field[newX][newY] = 3;
                intervalField[newX][newY] = 2;   
                i++;
            }
        }
    }
}


int main()
{
    srand(time(NULL));
    int timeInterval = 1;
    int initialX;
    int initialY;
    int numberOfCells;
    cout << "Input field size(height, width): " << endl;
    cin >> HEIGHT >> WIDTH;
    cout << "Input coordinates of infected cell (from 0 to " << HEIGHT-1 << " by heigth, from 0 to " << WIDTH-1 << " by width): " << endl;
    cin >> initialX >> initialY;
    cout << "Enter number of infected cells: " << endl;
    cin >> numberOfCells;

    int** field = new int*[WIDTH];
    int** intervalField = new int* [WIDTH];
    for (int i = 0; i < WIDTH; i++)
    {
        field[i] = new int[HEIGHT];
        intervalField[i] = new int[HEIGHT];
    }

    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            field[i][j] = 0;
            intervalField[i][j] = 1;
        }
    }

    fillField(field, intervalField, numberOfCells, initialX, initialY);
    

    while (true)
    {
        displayField(field);
        cout << "Current time: " << timeInterval << endl;
        infect(field, intervalField);
        timeInterval++;
        system("pause");
        system("cls");
    }

    for (int i = 0; i < WIDTH; i++)
    {
        delete[] field[i];
        delete[] intervalField[i];
    }

    delete[] field;
    delete[] intervalField;

    return 0;
    
}


