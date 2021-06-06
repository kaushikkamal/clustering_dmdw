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
    float recordId;
    float *p;
    char cluster, visited;
} RECORD;

typedef struct
{
    int label;
    int recordID;
    float b, c;
    // , c, d;
} dataLabel;

struct COLLECTION
{
    int noOfRecords;
    int noOfAttributes;
    // dataLabel *array;
    RECORD *array;
};

struct NODE
{
    int dataLabel;
    struct NODE *ptr;
};

typedef struct
{
    struct NODE *tos;
} STACK;

int push(STACK *s, int dataLabel)
{
    struct NODE *sNode;
    sNode = (struct NODE *)malloc(sizeof(struct NODE));
    if (sNode != NULL)
    {
        sNode->dataLabel = dataLabel;
        sNode->ptr = s->tos;
        s->tos = sNode;
        return 0;
    }
    return -1;
}

int pop(STACK *s)
{
    int deleted_value;
    struct NODE *tempSNode;

    if (s->tos == NULL)
        return -1;

    tempSNode = s->tos;
    deleted_value = tempSNode->dataLabel;
    s->tos = s->tos->ptr;
    tempSNode->ptr = NULL;
    free(tempSNode);

    return deleted_value;
}

int is_stack_empty(STACK s)
{
    return s.tos == NULL;
}

int initialize(struct COLLECTION *coll, int numAttr, int n)
{
    if (n <= 0)
        return -1;

    if (numAttr <= 0)
        return -2;

    coll->noOfRecords = n;
    coll->noOfAttributes = numAttr;
    coll->array = (RECORD *)malloc(n * sizeof(RECORD));

    if (coll->array != NULL)
        return 0;

    return -3;
}

int readData(struct COLLECTION coll)
{
    FILE *file;
    dataLabel d;
    char ch;
    int i, j, n;
    float dataPoints;

    i = 0;
    n = coll.noOfRecords;

    file = fopen("dataset.txt", "r");
    if (file == NULL)
        return -1;

    for (i = 0; i < coll.noOfRecords; i++)
    {
        coll.array->p = (float *)malloc(sizeof(float) * coll.noOfAttributes);

        for (j = 0; j <= coll.noOfAttributes; j++)
        {
            fscanf(file, "%f", &dataPoints);
            coll.array->p[j] = dataPoints;
            if (j == 0)
            {
                coll.array->recordId = coll.array->p[0];
            }
        }
        coll.array[i].cluster = 'UNCLASSIFIED';
        coll.array[i].visited = 'NOT_VISITED';
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

float distance(dataLabel a, dataLabel b)
{
    return sqrt(pow(a.b - b.b, 2) + pow(a.c - b.c, 2));
}

// int pam(struct COLLECTION coll, int k)
// {
//     int i, j, p, q, minCostRecordIndex, result;
//     float allMinTotalCost, totalCost, minCost, currentCost;
//     dataLabel *cluster;
//     STACK s;
//     s.tos = NULL;

//     cluster = (dataLabel *)malloc(k * sizeof(dataLabel));

//     if (cluster == NULL)
//         return -1;

//     // initial clusters
//     for (i = 0; i < k; i++)
//         cluster[i] = coll.array[i];

//     for (p = 0; p < k; p++)
//     {
//         allMinTotalCost = __FLT_MAX__;
//         for (q = 0; q < coll.n; q++)
//         {
//             totalCost = 0.0; // delete it

//             if (cluster[p].recordID != coll.array[q].recordID)
//             {
//                 cluster[p] = coll.array[q];
//             }

//             for (i = 0; i < coll.n; i++)
//             {
//                 minCost = __FLT_MAX__; // MAX FLOAT
//                 for (j = 0; j < k; j++)
//                 {
//                     currentCost = distance(coll.array[i], cluster[j]);
//                     if (currentCost < minCost)
//                     {
//                         // coll.array[i].label = j;
//                         result = push(&s, j);
//                         minCost = currentCost;
//                     }
//                 }
//                 totalCost += minCost;
//             }
//             if (totalCost < allMinTotalCost)
//             {
//                 allMinTotalCost = totalCost;
//                 minCostRecordIndex = q;
//             }
//         }

//         if (cluster[p].recordID != coll.array[minCostRecordIndex].recordID)
//         {
//             cluster[p] = coll.array[minCostRecordIndex];
//         }
//     }

//     // i = coll.n - 1;
//     // while (!is_stack_empty(s) && i <= 0)
//     // {
//     //     result = pop(&s);
//     //     coll.array[i].label = result;
//     //     i--;
//     // }
//     // while (!is_stack_empty(s))
//     // {
//     //     result = pop(&s);
//     //     printf("\n%d",result);
//     // }

//     for (i = 0; i < k; i++)
//         printf("\nCluster data %d: %f %f", cluster[i].recordID, cluster[i].b, cluster[i].c);
// }

int display_data(struct COLLECTION coll)
{
    int i, j;
    for (i = 0; i < coll.noOfRecords; i++)
    {
        for (j = 0; j < coll.noOfAttributes; j++)
        {
            if (j == 0)
            {
                printf("\nRecord ID: %f\nData: ", coll.array->recordId);
            }

            printf("%.1f  ", coll.array[i].p[j]);
        }
        printf("\n");
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
    int result, n, k, nA;
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
        printf("\nEnter the number of attributes of dataset: ");
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

    // result = pam(coll, k);

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
