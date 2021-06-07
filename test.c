// for (i = 0; i < numRe; i++)
// {
//     r->array[i].noOfAttributes = numAt;
//     r->array[i].p = (float *)malloc(sizeof(float) * numAt);
//     for (j = 0; j <= numAt; j++)
//     {
//         fscanf(f, "%f", &dataPoints);
//         r->array[i].p[j] = dataPoints;
//         if (j == 0)
//         {
//             r->array[i].recordId = r->array[i].p[j];
//         }
//     }
//     r->array[i].cluster = UNCLASSIFIED;
//     r->array[i].visited = NOT_VISITED;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int recordId;
    int label;
    float *p;
    // char cluster, visited;
} RECORD;

typedef struct
{
    int noOfRecords;
    int noOfAttributes;
    RECORD *array;
} COLLECTION;

typedef struct
{
    int noOfCluster;
    RECORD *clusterData;
} CLUSTER;

int initialize(COLLECTION *coll, int numAttr, int n)
{
    if (n <= 0)
        return -1;

    if (numAttr <= 0)
        return -2;

    coll->array = (RECORD *)malloc(n * sizeof(RECORD));

    if (coll->array != NULL)
    {
        coll->noOfRecords = n;
        coll->noOfAttributes = numAttr;
        return 0;
    }

    return -3;
}

int readData(COLLECTION coll)
{
    FILE *file;
    char ch;
    int i, j, n;
    float dataPoints;

    file = fopen("dataset.txt", "r");
    if (file == NULL)
        return -1;

    for (i = 0; i < coll.noOfRecords; i++)
    {
        coll.array[i].p = (float *)malloc(coll.noOfAttributes * sizeof(float));

        for (j = 0; j < coll.noOfAttributes; j++)
        {
            fscanf(file, "%f\t", &dataPoints);
            // printf("%.2f  ", dataPoints);
            coll.array[i].p[j] = dataPoints;
            if (j == 0)
            {
                coll.array[i].recordId = coll.array[i].p[j];
            }
        }
        // printf("\n");
        // coll.array[i].cluster = 'UN';
        // coll.array[i].visited = 'NOT';
    }

    // ch = fscanf(file, "%d\t%f\t%f\n", &(d.recordID), &(d.b), &(d.c));
    // // ch = fscanf(file, "%d\t%f\t%f\t%f\n", &(d.recordID), &(d.b), &(d.c), &(d.d));
    // while (ch != EOF && i < n)
    // {
    //     (coll.array)[i] = d;
    //     i++;
    //     ch = fscanf(file, "%d\t%f\t%f\n", &(d.recordID), &(d.b), &(d.c));
    //     // ch = fscanf(file, "%d\t%f\t%f\t%f\n", &(d.recordID), &(d.b), &(d.c), &(d.d));
    // }

    fclose(file);
    return 0;
}

// float distance(dataLabel a, dataLabel b)
// {
//     return sqrt(pow(a.b - b.b, 2) + pow(a.c - b.c, 2));
// }

int pam(COLLECTION coll, int k)
{
    int i, j, p, q, m, n, minCostRecordIndex, result;
    float allMinTotalCost, totalCost, minCost, currentCost, tempCostSum;
    CLUSTER cluster;

    cluster.clusterData = (RECORD *)malloc(k * sizeof(RECORD));

    if (cluster.clusterData == NULL)
        return -1;

    cluster.noOfCluster = k;

    // initial clusters
    for (i = 0; i < k; i++)
        cluster.clusterData[i] = coll.array[i];

    for (p = 0; p < k; p++)
    {
        allMinTotalCost = __FLT_MAX__;
        for (q = 0; q < coll.noOfRecords; q++)
        {
            totalCost = 0.0;

            if (cluster.clusterData[p].recordId != coll.array[q].recordId)
            {
                cluster.clusterData[p] = coll.array[q];
            }

            for (m = 0; m < coll.noOfRecords; m++)
            {
                minCost = __FLT_MAX__;
                for (n = 0; n < k; n++)
                {
                    tempCostSum = 0.0;
                    for (i = 0; i < coll.noOfAttributes; i++)
                    {
                        if (i != 0)
                        {
                            tempCostSum += pow((coll.array[m].p[i] - cluster.clusterData[n].p[i]), 2);
                        }
                    }
                    currentCost = sqrt(tempCostSum);
                    if (currentCost < minCost)
                    {
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

        if (cluster.clusterData[p].recordId != coll.array[minCostRecordIndex].recordId)
        {
            cluster.clusterData[p] = coll.array[minCostRecordIndex];
        }
    }

   
    for (m = 0; m < coll.noOfRecords; m++)
    {
        minCost = __FLT_MAX__;
        for (n = 0; n < k; n++)
        {
            tempCostSum = 0.0;
            for (i = 0; i < coll.noOfAttributes; i++)
            {
                if (i != 0)
                {
                    tempCostSum += pow((coll.array[m].p[i] - cluster.clusterData[n].p[i]), 2);
                }
            }
            currentCost = sqrt(tempCostSum);
           
            if (currentCost < minCost)
            {
                coll.array[m].label = n;
                minCost = currentCost;
            }
            // printf("\n\n");
        }
        // printf("\n%f\n\n",minCost);
    }
    result = display_data(coll);
    // display cluster
    // for (i = 0; i < k; i++)
    // {
    //     for (j = 0; j < coll.noOfAttributes; j++)
    //     {
    //         if (j == 0)
    //         {
    //             printf("\nCluster Record ID: %f\nData: ", cluster.clusterData[i].p[j]);
    //         }
    //         else
    //         {
    //             printf("%.1f  ", cluster.clusterData[i].p[j]);
    //         }
    //     }
    //     printf("\n");
    // }
    return 0;
}

int display_data(COLLECTION coll)
{
    int i, j;
    for (i = 0; i < coll.noOfRecords; i++)
    {
        for (j = 0; j < coll.noOfAttributes; j++)
        {
            if (j == 0)
            {
                printf("\nRecord ID: %f\nLabel: %f\nData: ", coll.array[i].p[j], coll.array[i].label);
            }
            else
            {
                printf("%.1f  ", coll.array[i].p[j]);
            }
        }
        printf("\n");
    }
    return 0;
}

int release_memory(COLLECTION coll)
{
    free(coll.array->p);
    free(coll.array);
    coll.array->p = NULL;
    coll.array = NULL;
    return 0;
}

int main()
{
    int result, n, k, nA;
    COLLECTION coll;

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
        printf("\nEnter the number of attributes of dataset(including record ID): ");
        scanf("%d", &nA);
        printf("\nEnter the number of records of dataset: ");
        scanf("%d", &n);
        result = initialize(&coll, nA, n);

        if (result == -1)
            printf("\nNumber of records should be greater than 0\n");
        else if (result == -2)
            printf("\nNumber of attributes should be greater than 0\n");
        else if (result == -3)
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

    printf("\nbefore pam\n\n");
    result = pam(coll, k);
    if (result != 0)
    {
        printf("\nError in pam!");
        return -1;
    }
    printf("\n\nafter in pam");

    // result = display_data(coll);
    // if (result != 0)
    // {
    //     printf("\nError in display!");
    //     return -1;
    // }

    result = release_memory(coll);
    if (result != 0)
    {
        printf("\nTerminated unsuccessfully");
        return -1;
    }
    return 0;
}
