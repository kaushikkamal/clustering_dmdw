#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int id;
    int label;
    float *data;
} RECORD;

typedef struct
{
    RECORD *clusterData;
} CLUSTER;

typedef struct
{
    int no_records;
    int no_attributes;
    RECORD *array;
} COLLECTION;

int PAM(COLLECTION collection, int k)
{
    CLUSTER c;
    int i, j, p, q, r, s;
    int loc;
    float cost1, cost2, cost3, cost4, cost5;

    c.clusterData = (RECORD *)malloc(sizeof(RECORD) * k);

    if (c.clusterData == NULL)
    {
        return -1;
    }

    for (i = 0; i < k; i++)
    {
        c.clusterData[i] = collection.array[i];
    }

    for (p = 0; p < k; p++)
    {
        cost5 = 100000000;
        for (q = 0; q < collection.no_records; q++)
        {
            cost4 = 0;
            c.clusterData[p] = collection.array[q];
            for (r = 0; r < collection.no_records; r++)
            {
                cost3 = 100000000;
                for (s = 0; s < k; s++)
                {
                    cost1 = 0;
                    for (i = 0; i < collection.no_attributes; i++)
                    {
                        if (i != 0)
                        {
                            cost1 += pow((collection.array[r].data[i] - c.clusterData[s].data[i]), 2);
                        }
                    }
                    if (sqrt(cost1) < cost3)
                    {
                        cost3 = sqrt(cost1);
                    }
                }
                cost4 += cost3;
            }
            if (cost4 < cost5)
            {
                cost5 = cost4;
                loc = q;
            }
        }

        if (c.clusterData[p].id != collection.array[loc].id)
        {
            c.clusterData[p] = collection.array[loc];
        }
    }

    for (r = 0; r < collection.no_records; r++)
    {
        cost3 = 100000000;
        for (s = 0; s < k; s++)
        {
            cost1 = 0.0;
            for (i = 0; i < collection.no_attributes; i++)
            {
                if (i != 0)
                {
                    cost1 += pow((collection.array[r].data[i] - c.clusterData[s].data[i]), 2);
                }
            }
            if (sqrt(cost1) < cost3)
            {
                cost3 = sqrt(cost1);
                (collection.array[r]).label = s;
            }
        }
    }

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < collection.no_attributes; j++)
        {
            if (j == 0)
                printf("\nCluster Record ID: %d\nData: ", c.clusterData[i].id);
            else
                printf("%.1f  ", c.clusterData[i].data[j]);
        }
        printf("\n");
    }
    return 0;
}

int initialize(COLLECTION *collection, int no_attributes, int no_records)
{
    FILE *file;
    char ch;
    int i, j, n;
    float dataPoints;
    if (no_records <= 0)
    {
        printf("\nNumber should be greater than 0\n");
        return -1;
    }
    if (no_attributes <= 0)
    {
        printf("\nNumber should be greater than 0\n");
        return -1;
    }
    collection->no_records = no_records;
    collection->no_attributes = no_attributes;
    collection->array = (RECORD *)malloc(no_records * sizeof(RECORD));

    if (collection->array == NULL)
    {
        printf("\nError\n");
        return -1;
    }
    file = fopen("dataset.txt", "r");
    if (file == NULL)
    {
        printf("\nError, cannot open file!");
        return -1;
    }
    for (i = 0; i < no_records; i++)
    {
        collection->array[i].data = (float *)malloc(sizeof(float) * no_attributes);
        for (j = 0; j < no_attributes; j++)
        {
            fscanf(file, "%f\t", &dataPoints);
            collection->array[i].data[j] = dataPoints;
            if (j == 0)
            {
                collection->array[i].id = collection->array[i].data[j];
            }
        }
    }
    fclose(file);
    return 0;
}

int display_data(COLLECTION collection)
{
    int i, j;
    for (i = 0; i < collection.no_records; i++)
    {
        for (j = 0; j < collection.no_attributes; j++)
        {
            if (j == 0)
            {
                printf("\nRecord ID: %d\nLabel: %d\nData: ", collection.array[i].id, collection.array[i].label);
            }
            else
            {
                printf("%.1f,  ", collection.array[i].data[j]);
            }
        }
        printf("\n");
    }
    return 0;
}

int main()
{
    int res, n, k, a;
    COLLECTION collection;

    printf("\nNumber of clusters: ");
    scanf("%d", &k);

    printf("\nNumber of records of dataset: ");
    scanf("%d", &n);

    printf("\nNumber of attributes of dataset with record ID: ");
    scanf("%d", &a);

    res = initialize(&collection, a, n);
    if (res != 0)
    {
        return -1;
    }

    res = PAM(collection, k);
    if (res != 0)
    {
        printf("\nError!");
        return -1;
    }

    res = display_data(collection);
    free(collection.array->data);
    free(collection.array);
    return 0;
}
