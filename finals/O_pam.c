#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int id;
    int label;
    float *values;
} RECORD;

typedef struct
{
    RECORD *clusters;
} CLUSTER;

typedef struct
{
    int no_attributes;
    int no_records;
    RECORD *records;
} COLLECTION;

int PAM(COLLECTION collection, int k)
{
    CLUSTER c;
    int i, j, p, q, r, s;
    int loc;
    float cost1, cost2, cost3, cost4, cost5;

    c.clusters = (RECORD *)malloc(sizeof(RECORD) * k);

    if (c.clusters == NULL)
    {
        return -1;
    }

    for (i = 0; i < k; i++)
    {
        c.clusters[i] = collection.records[i];
    }

    for (p = 0; p < k; p++)
    {
        cost5 = 100000000;
        for (q = 0; q < collection.no_records; q++)
        {
            cost4 = 0;
            c.clusters[p] = collection.records[q];
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
                            cost1 += pow((collection.records[r].values[i] - c.clusters[s].values[i]), 2);
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

        if (c.clusters[p].id != collection.records[loc].id)
        {
            c.clusters[p] = collection.records[loc];
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
                    cost1 += pow((collection.records[r].values[i] - c.clusters[s].values[i]), 2);
                }
            }
            if (sqrt(cost1) < cost3)
            {
                cost3 = sqrt(cost1);
                (collection.records[r]).label = s;
            }
        }
    }

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < collection.no_attributes; j++)
        {
            if (j == 0)
                printf("\nCluster Record ID: %d\nData: ", c.clusters[i].id);
            else
                printf("%.1f  ", c.clusters[i].values[j]);
        }
        printf("\n");
    }
    return 0;
}

int initialize_collection(COLLECTION *collection, int no_attributes, int no_records)
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
    collection->records = (RECORD *)malloc(no_records * sizeof(RECORD));

    if (collection->records == NULL)
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
        collection->records[i].values = (float *)malloc(sizeof(float) * no_attributes);
        for (j = 0; j < no_attributes; j++)
        {
            fscanf(file, "%f\t", &dataPoints);
            collection->records[i].values[j] = dataPoints;
            if (j == 0)
            {
                collection->records[i].id = collection->records[i].values[j];
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
                printf("\nRecord ID: %d\nLabel: %d\nData: ", collection.records[i].id, collection.records[i].label);
            }
            else
            {
                printf("%.1f,  ", collection.records[i].values[j]);
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

    res = initialize_collection(&collection, a, n);
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
    free(collection.records->values);
    free(collection.records);
    return 0;
}
