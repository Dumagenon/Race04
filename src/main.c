#include "mainhead.h"

// Функция создает новый файл и записывает в него готовый лаберинт
void map_write(int **arr, int dist, int exod, int *row, int *col, int *x, int *y) {
    int file = open("path.txt", O_WRONLY);
    if(file < 0) file = open("path.txt", O_WRONLY | O_CREAT);
    if (file < 0) {
        mx_printerr("error\n");
        return;
    }
    for(int i = 0; i < *row; i++) 
    {
        for(int j = 0; j < *col; j++)
        {
            if(arr[i][j] == -1) write(file, "#", 1);
            else if(arr[i][j] == 0) write(file, "*", 1);
            else if(arr[i][j] == -5 && dist != exod) write(file, "*", 1);
            else if(arr[i][j] == -5 && (*x == j && *y == i) && dist == exod) write(file, "X", 1);
            else if(arr[i][j] == dist) write(file, "D", 1);
            else write(file, ".", 1);
        }
        write(file, "\n", 1);
    }
    close(file);
}

// Функция считает колличество строк и символов ROW & COL
int count_row_col(const char *filename, int *rows, int *cols)
{
    char buf[1];
    if (filename == NULL) return -1;
    int srcFile = open(filename, O_RDONLY);
    if (srcFile < 0)
    {
        return -1;
    }

    int a = read(srcFile, buf, 1);
    while (a > 0)
    {
        if (buf[0] == '\n')
        {
            (*rows)++;
        }
        if (buf[0] != '\n' && buf[0] != ',')
        {
            (*cols)++;
        }
        a = read(srcFile, buf, 1);
    }

    if (buf[0] != '\n') (*rows) += 1;
    close(srcFile);

    if ((*cols) % (*rows) == 0) (*cols) /= (*rows);
    else return -2;
    
    if(*rows <= 1) return -1;
    return 1;
}

// Функция выписывает из файла символы в численный массив
int **arr_rewrite(const char *filename, int *rows, int *cols)
{
    if(filename == NULL) return NULL;
    int row = (*rows);
    int col = (*cols);

    // Выделили память под наш двухмерный массив
    int **arr = (int **)malloc(sizeof(int *) * row);

    for (int m = 0; m < row; m++)
    {
        arr[m] = (int *)malloc(sizeof(int) * col);
        for (int d = 0; d < col; d++)
        {
            arr[m][d] = 0;
        }
    }

    int i, j;
    char buf[1];
    int srcFile = open(filename, O_RDONLY);

    if (srcFile < 0) return NULL;

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col * 2; j++)
        {
            read(srcFile, buf, 1);
            if(buf[0] == ',') read(srcFile, buf, 1);
            if (buf[0] == '#')
            {
                arr[i][j] = -1;
            } else if (buf[0] == '.')
            {
                arr[i][j] = -2;
            } else if (buf[0] == '\n' || buf[0] == '\0') break;
            else 
            {
                close(srcFile);
                return 0;
            }
        }
    }
    close(srcFile);
    return arr;
}

int main(int argc, char const *argv[])
{

    if (argc != 6)
    {
        char s[] = "usage: ./race04 [file_name] [x1] [y1] [x2] [y2]\n";
        mx_printerr(s);
        return 0;
    }

    int cor_x1 = 0;  
    int cor_y1 = 0; 
    int cor_x2 = 0; 
    int cor_y2 = 0;

    if (!mx_atoi(argv[2], &cor_x1) || !mx_atoi(argv[3], &cor_y1) || !mx_atoi(argv[4], &cor_x2) || !mx_atoi(argv[5], &cor_y2) )
    {
        mx_printerr("error\n");
        return 0;
    }

    if (cor_x1 < 0 || cor_y1 < 0 || cor_x2 < 0 || cor_y2 < 0)
    {
        mx_printerr("points are out of map range\n");
        return 0;
    }
    
    if (argc == 6)
    {
        int row = 0, col = 0;
        int exod = 0, dist = 0;
        int counter = count_row_col(argv[1], &row, &col);
        // Error
        if (counter == -1)
        {
            mx_printerr("map does not exist\n");
            return 0;
        } 
        else if (counter == -2)
        {
            mx_printerr("map error\n");
            return 0;
        } else if (cor_x1 >= row || cor_y1 >= col || cor_x2 >= col || cor_y2 >= row)
        {
            mx_printerr("points are out of map range\n");
            return 0;
        }

        int **map = arr_rewrite(argv[1], &row, &col); // Initialize the map
        
        // Errors
        
        if(map == 0)
        {
            mx_printerr("map error\n");
            return 0;
        }
        if(map == NULL)
        {
            mx_printerr("map does not exist\n");
            return 0;
        }
        if(map[cor_x1][cor_y1] == -1)
        {
            mx_printerr("entry point cannot be an obstacle\n");
            return 0;
        }
        if(map[cor_y2][cor_x2] == -1)
        {
            mx_printerr("exit point cannot be an obstacle\n");
            return 0;
        }

        // ------------------------------- Распространение волны -------------------------------

        int dx[4] = {1, 0, -1, 0};   // смещения, соответствующие соседям ячейки
        int dy[4] = {0, 1, 0, -1};   // справа, снизу, слева и сверху

        int swap = 1, len;
        int i, j, d, k;

        d = 0;
        if (map[cor_x1][cor_y1] != -1)
        {
            map[cor_x1][cor_y1] = 0; // стартовая ячейка помечена 0
            while(swap != 0) {
                swap = 0;
                for(i = 0; i < row; ++i) 
                    for(j = 0; j < col; ++j) 
                        if(map[i][j] == d)
                        {
                            for(k = 0; k < 4; ++k) {
                                int iy = i + dy[k], ix = j + dx[k];
                                if ( iy >= 0 && iy < row && ix >= 0 && ix < col && map[iy][ix] == -2 )
                                {
                                    swap = 1;            // найдены непомеченные клетки
                                    map[iy][ix] = d + 1;      // распространяем волну
                                }
                            }
                        }
                d++;
            }
        } else
        {
            mx_printerr("!entry point cannot be an obstacle\n");
            return 0;
        }

        // Error
        if(map[cor_y2][cor_x2] == -2) {       // Путь не найден
            mx_printerr("route not found\n");
            return 0;
        } 

        // ------------------------------- Восстановление пути -------------------------------
        int px[col * row], py[col * row];

        dist = d - 1;
        len = map[cor_y2][cor_x2]; // длина кратчайшего пути из (ax, ay) в (bx, by)
        i = cor_x2;
        j = cor_y2;
        d = len;
        while ( d > 0 )
        {
            px[d] = i;
            py[d] = j; // записываем ячейку (x, y) в путь
            d--;
            for (k = 0; k < 4; ++k)
            {
                int iy = j + dy[k], ix = i + dx[k];
                if ( iy >= 0 && iy < row && ix >= 0 && ix < col &&
                    map[iy][ix] == d)
                {
                    map[iy][ix] = 0;
                    exod++;
                    i = i + dx[k];
                    j = j + dy[k]; // переходим в ячейку, которая на 1 ближе к старту
                    break;
                }
            }
            map[cor_y2][cor_x2] = -5;
        }

        px[0] = cor_x1;
        py[0] = cor_y1; // теперь px[0..len] и py[0..len] - координаты ячеек пути

        // Write map 
        map_write(map, dist, exod, &row, &col, &cor_x2, &cor_y2);

        mx_printstr("dist=");
        mx_printint(dist);
        mx_printchar('\n');
        mx_printstr("exit=");
        mx_printint(exod);
        mx_printchar('\n');

        free(map);
    } else
    {
        char s[] = "error\n";
        mx_printerr(s);
        exit(1);
    }
    return 0;
}
