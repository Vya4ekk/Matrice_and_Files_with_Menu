#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h> 
#include <iomanip>
#include <math.h>
#include <fstream>

using namespace std;

void Initialize(int** arr,int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = new int[size];
    }
}

void delete_array(int** arr,int size)
{
    for (int i = 0; i < size; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

int Sum(int **arr,int size)
{
    int result = 0;
    for (int i = 1; i < size; i += 2)
    {
        for (int j = 0; j < size; j++)
        {
            result += arr[j][i];
        }
    }
    return result;
}

int Count_rows( int **arr,int size)
{
    int count_result = size;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i][j] == 0) count_result -= 1, j = size;
        }
    }
    return count_result;
}

void Sort_diagonale(int **arr,int size)
{
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - 1; j++)
            {
                if (arr[j + 1][j + 1] < arr[j][j]) swap(arr[j + 1][j + 1], arr[j][j]);
            }
        }
}

void Rand(int **arr,int size)
{     
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = rand() % 99;
        }
    }
}

void Show_array(int **arr,int size)
{
    int column = 0;
    for (int i = 0; i < size; i++)
    {
        cout << "    " << i;
    }
    cout << "\n    ________________________________\n  |\n";
    for (int i = 0; i < size; i++)
    {
        cout << column << " " << "|";
        for (int j = 0; j < size; j++)
        {
            cout << setw(3) << arr[i][j] << "  ";
        }
        column++;
        cout << "\n  |\n";
    }
}

void Hands_write(int** arr,int size)
{
    int n = 0, i = 0, j = 0;
    while (true)
    {
        Show_array(arr, size);
        cout << "\n\n\nВведите элемент "; cin >> n;       
        system("cls");
        arr[i][j] = n;
        if (i == size - 1 && j == size - 1) break;
        if (j == size) ++i, j = 0;
        ++j;      
    }
}

void File_output(int **&arr, int &size)
{
    SetConsoleCP(1251);
    cout << "Введите путь к файлу ";
    char path[100];
    cin >> path;
    fstream file;
    file.open(path);
    while (!file)
    {
        cout << "Введите верный путь к файлу\n\n";
        cin >> path;
        file.open(path);
    }
    file >> size;
    if (size < 7)
    {
        cout << "Размеры матрицы меньше 7 проверьте целостность файла или измените матрицу" << endl;
        exit(0);
    }
    arr = new int* [size];
    Initialize(arr, size);

    for (int i = 0; i < size; i++)
    {
       for (int j = 0; j < size; j++)
       {
            file >> arr[i][j];
       }
    }

    file.close();
    SetConsoleCP(866);
}

void File_input(int **arr, int size)
{
    SetConsoleCP(1251);
    cout << "Введите путь к файлу ";
    char path[100];
    cin >> path;
    fstream file;
    file.open(path, fstream::in | fstream::app);
    while (!file.is_open()) 
    {
        cout << "Введите верный путь к файлу\n\n";
        cin >> path;
        file.open(path, fstream::in | fstream::app);
    }      

        file << size << endl;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                file << setw(3) << arr[i][j];
            }
            file << endl;
        }
        file.close();
        SetConsoleCP(866);
}

void menu1()
{
    system("cls");
    cout << " Заполнить массив рандомно\n"
        << " Ввести из файла\n";
}

void menu2() 
{
    system("cls");
    cout << " Сумма элементов непарных столбцов\n"
        << " Количество столбцов без нулевых элементов\n"
        << " Упорядочить главную диагональ\n"
        << " Продолжить\n";
}

void menu3()
{
    system("cls");
    cout <<"\t\t Записать в файл?\n"
         << " ДА\n"
         << " НЕТ\n";
}

void GoToXY(short position_Y)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hStdOut, { 0, position_Y });
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    SetConsoleTitle(L"LAB 7");
    int COUNT_OF_FUNCTIONS = 1;
    bool openedmenu = true;
    short key = 0, positionkey = 0;
    int size, ** arr = nullptr;

    while (openedmenu) {
        menu1();
        GoToXY(positionkey);
        key = _getch();
        if (key == 224) key = _getch();
        switch (key)
        {
        case 27: //выход
            exit(0);
            break;
        case 80: //стрелка вниз
            positionkey++;
            break;
        case 72: //стрелка вверх
            positionkey--;
            break;
        case 13: //Энтер
            switch (positionkey)
            {
            case 0:           
                system("cls");
                cout << "Введите размер матрицы ";
                cin >> size;
                while (size < 7)
                {
                    cout << "Введите размер больше семи";
                    cin >> size;
                }
                arr = new int* [size];
                Initialize(arr, size);
                Rand(arr, size);
                Show_array(arr, size);
                system("pause");
                openedmenu = false;
                break;            
            case 1:            
                system("cls");
                File_output(arr, size);
                Show_array(arr, size);
                system("pause");
                openedmenu = false;
                break;
            
            }
            break;
        }
        if (positionkey < 0) positionkey = 0;
        if (positionkey > COUNT_OF_FUNCTIONS) positionkey = COUNT_OF_FUNCTIONS;
    }

    openedmenu = true;
    while (openedmenu) {
        COUNT_OF_FUNCTIONS = 3;
        menu2();
        GoToXY(positionkey);
        key = _getch();
        if (key == 224) key = _getch();
        switch (key)
        {
        case 27: //выход
            openedmenu = false;
            break;
        case 80: //стрелка вниз
            positionkey++;
            break;
        case 72: //стрелка вверх
            positionkey--;
            break;
        case 13: //Энтер
            switch (positionkey)
            {
            case 0:
                system("cls");
                cout << "Сумма всех элементов непарных столбцов = " << Sum(arr, size) << endl;
                Show_array(arr, size);
                system("pause");
                break;
            case 1:
                system("cls");
                cout << "Количество строчек без нулевых элементов = " << Count_rows(arr, size) << endl;
                Show_array(arr, size);
                system("pause");
                break;
            case 2:
                system("cls");
                Sort_diagonale(arr, size);
                cout << "Массив отсортирован\n";
                Show_array(arr, size);
                system("pause");
                break;
            case 3:
                system("cls");
                openedmenu = false;
                break;
            }
        }
        if (positionkey < 0) positionkey = 0;
        if (positionkey > COUNT_OF_FUNCTIONS) positionkey = COUNT_OF_FUNCTIONS;
    }

    key = 1; positionkey = 1; COUNT_OF_FUNCTIONS = 2;
    openedmenu = true;
    while (openedmenu) {
        menu3();
        GoToXY(positionkey);
        key = _getch();
        if (key == 224) key = _getch();
        switch (key)
        {
        case 27: //выход
            exit(0);
            break;
        case 80: //стрелка вниз
            positionkey++;
            break;
        case 72: //стрелка вверх
            positionkey--;
            break;
        case 13: //Энтер
            switch (positionkey)
            {
            case 1:
                system("cls");
                File_input(arr, size);
                delete_array(arr, size);
                openedmenu = false;
                break;
            case 2:
                system("cls");
                delete_array(arr, size);
                openedmenu = false;
                break;
            }
            break;
        }
        if (positionkey < 1) positionkey = 1;
        if (positionkey > COUNT_OF_FUNCTIONS) positionkey = COUNT_OF_FUNCTIONS;
    }
    return 0;
}