#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int recordId, label;
    float *data;
} RECORD;

typedef struct
{
    int numRecords, numAttributes;
    RECORD *array;
} COLLECTION;

typedef struct
{
    int numCluster;
    RECORD *clusterData;
} CLUSTER;

int initialize(COLLECTION *, int, int);
int readData(COLLECTION, char **);
int pam(COLLECTION, int);
int displayData(COLLECTION);
int releaseMemory(COLLECTION);

int main()
{
    int result, numRecords, numCluster, numAttributes;
    COLLECTION coll;
    char *fileName;
    fileName = (char *)malloc(sizeof(char) * 25);

    do
    {
        printf("\nEnter the number of clusters: ");
        scanf("%d", &numCluster);

        if (numCluster < 1)
            printf("\nThe number of clusters should be greater than 0\n");
        else
            break;

    } while (numCluster < 1);

    do
    {
        printf("\nEnter the number of attributes of dataset(including record ID): ");
        scanf("%d", &numAttributes);

        printf("\nEnter the number of records of dataset: ");
        scanf("%d", &numRecords);

        result = initialize(&coll, numAttributes, numRecords);

        if (result == -1)
            printf("\nNumber of records should be greater than 0\n");
        else if (result == -2)
            printf("\nNumber of attributes should be greater than 0\n");
        else if (result == -3)
            printf("\nMemory is not allocated\n");
        else
            break;

    } while (result != 0);

    printf("\nEnter the file name with extension: ");
    scanf("%s", fileName);

    result = readData(coll, &fileName);
    free(fileName);

    if (result != 0)
    {
        printf("\nCannot open file!");
        return -1;
    }

    result = pam(coll, numCluster);
    if (result != 0)
    {
        printf("\nError in pam!");
        return -1;
    }

    result = displayData(coll);
    if (result != 0)
    {
        printf("\nError in display!");
        return -1;
    }

    result = releaseMemory(coll);
    if (result != 0)
    {
        printf("\nTerminated unsuccessfully");
        return -1;
    }
    return 0;
}

int initialize(COLLECTION *coll, int numAttributes, int numRecords)
{
    if (numRecords <= 0)
        return -1;

    if (numAttributes <= 0)
        return -2;

    coll->array = (RECORD *)malloc(numRecords * sizeof(RECORD));

    if (coll->array != NULL)
    {
        coll->numRecords = numRecords;
        coll->numAttributes = numAttributes;
        return 0;
    }

    return -3;
}

int readData(COLLECTION coll, char **fileName)
{
    FILE *file;
    int i, j, n;
    float dataPoints;

    file = fopen(*fileName, "r");
    if (file == NULL)
        return -1;

    for (i = 0; i < coll.numRecords; i++)
    {
        coll.array[i].data = (float *)malloc(coll.numAttributes * sizeof(float));

        for (j = 0; j < coll.numAttributes; j++)
        {
            fscanf(file, "%f\t", &dataPoints);
            coll.array[i].data[j] = dataPoints;

            if (j == 0)
            {
                coll.array[i].recordId = coll.array[i].data[j];
                coll.array[i].label = -1;
            }
        }
    }
    fclose(file);
    // free(fileName);
    return 0;
}

int pam(COLLECTION coll, int k)
{
    int p, q, m, n, i, minCostRecordIndex;
    float allMinTotalCost, totalCost, minCost, currentCost, tempCostSum;
    CLUSTER cluster;

    cluster.clusterData = (RECORD *)malloc(k * sizeof(RECORD));

    if (cluster.clusterData == NULL)
        return -1;

    cluster.numCluster = k;

    for (i = 0; i < k; i++)
        cluster.clusterData[i] = coll.array[i];

    for (p = 0; p < k; p++)
    {
        allMinTotalCost = __FLT_MAX__; // max float
        for (q = 0; q < coll.numRecords; q++)
        {
            totalCost = 0.0;

            if (cluster.clusterData[p].recordId != coll.array[q].recordId)
                cluster.clusterData[p] = coll.array[q];

            for (m = 0; m < coll.numRecords; m++)
            {
                minCost = __FLT_MAX__;
                for (n = 0; n < k; n++)
                {
                    tempCostSum = 0.0;

                    for (i = 0; i < coll.numAttributes; i++)
                        if (i != 0)
                            tempCostSum += pow((coll.array[m].data[i] - cluster.clusterData[n].data[i]), 2);

                    currentCost = sqrt(tempCostSum);

                    if (currentCost < minCost)
                        minCost = currentCost;
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
            cluster.clusterData[p] = coll.array[minCostRecordIndex];
    }

    for (m = 0; m < coll.numRecords; m++)
    {
        minCost = __FLT_MAX__;
        for (n = 0; n < k; n++)
        {
            tempCostSum = 0.0;

            for (i = 0; i < coll.numAttributes; i++)
                if (i != 0)
                    tempCostSum += pow((coll.array[m].data[i] - cluster.clusterData[n].data[i]), 2);

            currentCost = sqrt(tempCostSum);

            if (currentCost < minCost)
            {
                (coll.array[m]).label = n + 1;
                minCost = currentCost;
            }
        }
    }

    printf("\nClusters ->\n\n");
    for (m = 1; m <= k; m++)
    {
        printf("Cluster %d :", m);
        for (n = 0; n < coll.numRecords; n++)
            if (m == coll.array[n].label)
                printf(" %d,", coll.array[n].recordId);

        printf("\n");
    }

    return 0;
}

int displayData(COLLECTION coll)
{
    int i, j;
    printf("\nData ->\n");
    for (i = 0; i < coll.numRecords; i++)
    {
        for (j = 0; j < coll.numAttributes; j++)
        {
            if (j == 0)
                printf("\nRecord ID: %d\nLabel: %d\nData: ", coll.array[i].recordId, coll.array[i].label);
            else
                printf("%.1f,  ", coll.array[i].data[j]);
        }
        printf("\n");
    }
    return 0;
}

int releaseMemory(COLLECTION coll)
{
    free(coll.array->data);
    free(coll.array);
    coll.array->data = NULL;
    coll.array = NULL;
    return 0;
}