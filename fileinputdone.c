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
