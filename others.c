#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int recordID;
    float b, c;
} DATAPOINTS;

typedef struct
{
    int n;
    DATAPOINTS *array;
} COLLECTION;

int init(COLLECTION *c, int n)
{
    c->n = n;
    c->array = (DATAPOINTS *)malloc(n * sizeof(DATAPOINTS));
    return 0;
}

int readData(COLLECTION c)
{
    FILE *file;
    DATAPOINTS d;
    char ch;
    int i, n;

    i = 0;
    n = c.n;

    file = fopen("dataset.txt", "r");
    if (file == NULL)
        return -1;

    ch = fscanf(file, "%d\t%f\t%f\n", &(d.recordID), &(d.b), &(d.c));
    while (ch != EOF && i < n)
    {
        (c.array)[i] = d;
        i++;
        ch = fscanf(file, "%d\t%f\t%f\n", &(d.recordID), &(d.b), &(d.c));
    }

    fclose(file);
    return 0;
}

int display_data(COLLECTION c)
{
    int i;
    for (i = 0; i < c.n; i++)
    {
        printf("\nData %d: %.1f %.1f", (c.array)[i].recordID, (c.array)[i].b, (c.array)[i].c);
    }
    return 0;
}

int main()
{
    int result, n, k;
    COLLECTION c;

    printf("\nEnter the number of clusters: ");
    scanf("%d", &k);
    printf("\nEnter the number of records of dataset: ");
    scanf("%d", &n);

    result = init(&c, n);
    result = readData(c);
    result = display_data(c);

    return 0;
}