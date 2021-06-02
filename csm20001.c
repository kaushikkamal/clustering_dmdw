#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int a;
    float b, c, d;
} DATA;

struct COLLECTION
{
    int n;
    DATA *array;
};

int initialize(struct COLLECTION *coll)
{
    int n;
    n = 5; // no of records
    coll->n = n;
    printf("initialize 1");
    coll->array = (DATA *)malloc(n * sizeof(DATA));
    printf("initialize 2");
    if (coll->array == NULL)
    {
        coll->n = 0;
        return -1;
    }
    return 0;
}

int readData(struct COLLECTION *coll)
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

    int i = 0;
    while (ch != EOF)
    {
        (coll->array)[i] = d;
        i++;
        ch = fscanf(file, "%d\t%f\t%f\t%f\n", &(d.a), &(d.b), &(d.c), &(d.d));
    }

    fclose(file);
}

int display_data(struct COLLECTION *coll)
{
    int i;
    for (i = 0; i < coll->n; i++)
    {
        printf("\nData %d: %f %f %f", (coll->array)[i].a, (coll->array)[i].b, (coll->array)[i].c, (coll->array)[i].d);
    }
    return 0;
}

int main()
{
    int result;
    struct COLLECTION coll;
    printf("0");
    result = initialize(&coll);
    if (result != 0)
    {
        printf("\nError in initialization!");
        return -1;
    }

    result = readData(&coll);
    if (result != 0)
    {
        printf("\nError in initialization!");
        return -1;
    }
    result = display_data(&coll);
    if (result != 0)
    {
        printf("\nError in display!");
        return -1;
    }
    return 0;
}
