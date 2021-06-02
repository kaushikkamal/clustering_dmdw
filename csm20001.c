#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int recordID;
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
    coll->array = (DATA *)malloc(n * sizeof(DATA));
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
    int i;

    i = 0;
    file = fopen("dataset.txt", "r");

    if (file == NULL)
    {
        return -1;
    }

    ch = fscanf(file, "%d\t%f\t%f\t%f\n", &(d.recordID), &(d.b), &(d.c), &(d.d));
    while (ch != EOF)
    {
        (coll->array)[i] = d;
        i++;
        ch = fscanf(file, "%d\t%f\t%f\t%f\n", &(d.recordID), &(d.b), &(d.c), &(d.d));
    }

    fclose(file);
    return 0;
}

int display_data(struct COLLECTION *coll)
{
    int i;
    for (i = 0; i < coll->n; i++)
    {
        printf("\nData %d: %f %f %f", (coll->array)[i].recordID, (coll->array)[i].b, (coll->array)[i].c, (coll->array)[i].d);
    }
    return 0;
}

int release_memory(struct COLLECTION coll)
{
    free(coll.array);
    coll.array == NULL;
    return 0;
}

int main()
{
    int result;
    struct COLLECTION coll;
    result = initialize(&coll);
    if (result != 0)
    {
        printf("\nError in initialization!");
        return -1;
    }

    result = readData(&coll);
    if (result != 0)
    {
        printf("\nCannot open file!");
        return -1;
    }
    result = display_data(&coll);
    if (result != 0)
    {
        printf("\nError in display!");
        return -1;
    }

    result = release_memory(coll);
    if (result != 0)
    {
        printf("\nTerminated unsuccessfully");
        return -1;
    }
    return 0;
}
