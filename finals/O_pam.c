#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int id;
    int label;
    float *values;
} DATA;

typedef struct
{
    DATA *clusters;
} CLUSTER;

typedef struct
{
    int no_attributes;
    int no_records;
    DATA *records;
} DATASET;

int PAM(DATASET data_set, int k)
{
    CLUSTER c;
    int i, j, p, q, r, s;
    int loc;
    float cost1, cost2, cost3, cost4, cost5;

    c.clusters = (DATA *)malloc(sizeof(DATA) * k);

    if (c.clusters == NULL)
    {
        return -1;
    }

    for (i = 0; i < k; i++)
    {
        c.clusters[i] = data_set.records[i];
    }

    for (p = 0; p < k; p++)
    {
        cost5 = 100000000;
        for (q = 0; q < data_set.no_records; q++)
        {
            cost4 = 0;
            c.clusters[p] = data_set.records[q];
            for (r = 0; r < data_set.no_records; r++)
            {
                cost3 = 100000000;
                for (s = 0; s < k; s++)
                {
                    cost1 = 0;
                    for (i = 0; i < data_set.no_attributes; i++)
                    {
                        if (i != 0)
                        {
                            cost1 += pow((data_set.records[r].values[i] - c.clusters[s].values[i]), 2);
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

        if (c.clusters[p].id != data_set.records[loc].id)
        {
            c.clusters[p] = data_set.records[loc];
        }
    }

    for (r = 0; r < data_set.no_records; r++)
    {
        cost3 = 100000000;
        for (s = 0; s < k; s++)
        {
            cost1 = 0.0;
            for (i = 0; i < data_set.no_attributes; i++)
            {
                if (i != 0)
                {
                    cost1 += pow((data_set.records[r].values[i] - c.clusters[s].values[i]), 2);
                }
            }
            if (sqrt(cost1) < cost3)
            {
                cost3 = sqrt(cost1);
                (data_set.records[r]).label = s;
            }
        }
    }

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < data_set.no_attributes; j++)
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

int initialize_collection(DATASET *data_set, int no_attributes, int no_records)
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
    data_set->no_records = no_records;
    data_set->no_attributes = no_attributes;
    data_set->records = (DATA *)malloc(no_records * sizeof(DATA));

    if (data_set->records == NULL)
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
        data_set->records[i].values = (float *)malloc(sizeof(float) * no_attributes);
        for (j = 0; j < no_attributes; j++)
        {
            fscanf(file, "%f\t", &dataPoints);
            data_set->records[i].values[j] = dataPoints;
            if (j == 0)
            {
                data_set->records[i].id = data_set->records[i].values[j];
            }
        }
    }
    fclose(file);
    return 0;
}

int display_data(DATASET data_set)
{
    int i, j;
    for (i = 0; i < data_set.no_records; i++)
    {
        for (j = 0; j < data_set.no_attributes; j++)
        {
            if (j == 0)
            {
                printf("\nRecord ID: %d\nLabel: %d\nData: ", data_set.records[i].id, data_set.records[i].label);
            }
            else
            {
                printf("%.1f,  ", data_set.records[i].values[j]);
            }
        }
        printf("\n");
    }
    return 0;
}

int main()
{
    int res, n, k, a;
    DATASET data_set;

    printf("\nNumber of clusters: ");
    scanf("%d", &k);

    printf("\nNumber of records of dataset: ");
    scanf("%d", &n);

    printf("\nNumber of attributes of dataset with record ID: ");
    scanf("%d", &a);

    res = initialize_collection(&data_set, a, n);
    if (res != 0)
    {
        return -1;
    }

    res = PAM(data_set, k);
    if (res != 0)
    {
        printf("\nError!");
        return -1;
    }
    res = display_data(data_set);
    free(data_set.records->values);
    free(data_set.records);
    return 0;
}
