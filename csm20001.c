#include <stdio.h>
typedef struct
{
    int a;
    float b, c, d;
} DATA;

int main()
{
    FILE *file;
    DATA d;
    char ch;

    file = fopen("dataset.txt", "r");

    if (file == NULL)
    {
        printf("Cannot open file!\n");
        return 0;
    }

    
    ch = fscanf(file, "%d\t%f\t%f\t%f\n", &(d.a), &(d.b), &(d.c), &(d.d));

    while (ch != EOF)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n", d.a, d.b, d.c, d.d);
        ch = fscanf(file, "%d\t%f\t%f\t%f\n", &(d.a), &(d.b), &(d.c), &(d.d));
    }

    fclose(file);
    return 0;
}

// int main()
// {
//     FILE *file;

//     char ch;

//     file = fopen("dataset.txt", "r");
//     if (file == NULL)
//     {
//         printf("Cannot open file \n");
//         return 0;
//     }

//     ch = fgetc(file);
//     DATA d;
//     while (ch != EOF)
//     {

//         fgets(file, "%f\t%f\t%f\t%f", d.a, d.b, d.c, d.c);
//         ch = fgetc(file);
//     }

//     printf("%f, %f,%f, %f", &(d.a), &(d.b), &(d.c), &(d.d));

//     fclose(file);
//     return 0;
// }

// int main()
// {
//     FILE *file;
//     DATA d;
//     int scanned = 0;
//     float some_ints[4];
//     int i = 0;
//     for (i = 0; i < 4; i++)
//     {
//         some_ints[i] = 0.0;
//     }

//     file = fopen("dataset.txt", "r");
//     while ((scanned = fscanf(file, "%f %f %f %f", some_ints, some_ints + 1, some_ints + 2, some_ints + 3)) != EOF)
//     {
//         if (scanned == 4)
//         {
//             printf("%f %f %f %f\n", some_ints[0], some_ints[1], some_ints[2], some_ints[3], some_ints[4]);
//         }
//         else
//         {
//             printf("Whoops! Input format is incorrect!\n");
//             break;
//         }
//     }
//     return 0;
// }