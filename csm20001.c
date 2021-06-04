#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct
{
    int label;
    int recordID;
    float b, c;
    // , c, d;
} DATA;

struct COLLECTION
{
    int n, k; // check
    DATA *array;
};

int initialize(struct COLLECTION *coll, int n)
{
    if (n <= 0)
        return -1;

    coll->n = n;
    coll->array = (DATA *)malloc(n * sizeof(DATA));

    if (coll->array != NULL)
        return 0;

    coll->n = 0;
    return -2;
}

int readData(struct COLLECTION coll)
{
    FILE *file;
    DATA d;
    char ch;
    int i, n;

    i = 0;
    n = coll.n;

    file = fopen("dataset.txt", "r");
    if (file == NULL)
        return -1;

    ch = fscanf(file, "%d\t%f\t%f\n", &(d.recordID), &(d.b), &(d.c));
    // ch = fscanf(file, "%d\t%f\t%f\t%f\n", &(d.recordID), &(d.b), &(d.c), &(d.d));
    while (ch != EOF && i < n)
    {
        (coll.array)[i] = d;
        i++;
        ch = fscanf(file, "%d\t%f\t%f\n", &(d.recordID), &(d.b), &(d.c));
        // ch = fscanf(file, "%d\t%f\t%f\t%f\n", &(d.recordID), &(d.b), &(d.c), &(d.d));
    }

    fclose(file);
    return 0;
}

float distance(DATA a, DATA b)
{
    // return sqrt((a.b - b.b) * (a.b - b.b) + (a.c - b.c) * (a.c - b.c));
    return sqrt(pow(a.b - b.b, 2) + pow(a.c - b.c, 2));
}

int pam(struct COLLECTION coll, int k)
{
    int i, j, p, q, minCostRecordIndex;
    float allMinTotalCost, totalCost, minCost, currentCost;
    DATA *cluster;

    cluster = (DATA *)malloc(k * sizeof(DATA));

    if (cluster == NULL)
        return -1;

    // initial clusters
    for (i = 0; i < k; i++)
        cluster[i] = coll.array[i];

    for (p = 0; p < k; p++)
    {
        allMinTotalCost = __FLT_MAX__;
        for (q = 0; q < coll.n; q++)
        {
            totalCost = 0.0; // delete it

            if (cluster[p].recordID != coll.array[q].recordID)
            {
                cluster[p] = coll.array[q];
            }

            for (i = 0; i < coll.n; i++)
            {
                minCost = __FLT_MAX__; // MAX FLOAT
                for (j = 0; j < k; j++)
                {
                    currentCost = distance(coll.array[i], cluster[j]);
                    if (currentCost < minCost)
                    {
                        coll.array[i].label = j;
                        minCost = currentCost;
                    }
                }
                totalCost += minCost;
            }
            if (totalCost < allMinTotalCost)
            {
                allMinTotalCost = totalCost;
                minCostRecordIndex = q;
            }
        }
        cluster[p] = coll.array[minCostRecordIndex];
    }
    // for (i = 0; i < k; i++)
    //     printf("\nCluster data %d: %f %f", cluster[i].recordID, cluster[i].b, cluster[i].c);
}

int display_data(struct COLLECTION coll)
{
    int i;
    for (i = 0; i < coll.n; i++)
    {
        printf("\nData %d: %.1f %.1f Label %d", (coll.array)[i].recordID, (coll.array)[i].b, (coll.array)[i].c, (coll.array)[i].label);
        // printf("\nData %d: %f %f %f", (coll->array)[i].recordID, (coll->array)[i].b, (coll->array)[i].c, (coll->array)[i].d);
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
    int result, n, k;
    struct COLLECTION coll;

    // read clursted number
    do
    {
        printf("\nEnter the number of clusters: ");
        scanf("%d", &k);

        if (k < 1)
            printf("\nThe number of clusters should be greater than 0\n");
        else
            break;

    } while (k < 1);
    // end read clursted number

    // read number of records of dataset
    do
    {
        printf("\nEnter the number of records of dataset: ");
        scanf("%d", &n);
        result = initialize(&coll, n);

        if (result == -1)
            printf("\nEntered value should be greater than 0\n");
        else if (result == -2)
            printf("\nMemory is not allocated\n");
        else
            break;

    } while (result != 0);

    // end read number of records of dataset

    if (result != 0)
    {
        printf("\nError in initialization!");
        return -1;
    }

    result = readData(coll);
    if (result != 0)
    {
        printf("\nCannot open file!");
        return -1;
    }

    result = pam(coll, k);

    result = display_data(coll);
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
