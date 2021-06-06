#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 1000
typedef struct cluster
{
	int label;
	int data;
	struct cluster *next;
} C;

int abs(int num)
{
	if (num < 0)
		return -num;
	return num;
}

int viewCluster(C *cluster)
{
	C *tmp = cluster;
	printf("==========Displaying==========\n");
	while (tmp)
	{
		printf("Data: %d\n", tmp->data);
		printf("Cluster: %d\n", tmp->label);
		tmp = tmp->next;
	}
	return 0;
}
int main()
{
	int arr[] = {3, 15, 2, 17, 18, 1};
	// int arr[] = {10, 55, 15, 56, 50, 11};
	C *final_cluster = NULL;
	C *head = NULL;
	int best_cost = 10000000; //High best cost to update
	int current_cost;

	int first_i = 0, second_i = 1; //Random K
	int k1, k2;					   //2 For 2 clusters
	int i;

	int cost1, cost2;

	k1 = arr[first_i];
	k2 = arr[second_i];

	while (first_i != 6)
	{
		k1 = arr[first_i];
		k2 = arr[second_i];
		current_cost = 0;
		C *tmp = NULL;
		for (i = 0; i < 6; i++)
		{
			cost1 = abs(k1 - arr[i]);
			cost2 = abs(k2 - arr[i]);

			C *new_temp = (C *)malloc(sizeof(C));

			if (tmp == NULL)
			{
				tmp = new_temp;
				head = tmp;
			}
			else
			{
				tmp->next = new_temp;
			}
			if (cost1 < cost2)
			{
				new_temp->label = 0;
				current_cost += cost1;
			}
			else
			{
				new_temp->label = 1;
				current_cost += cost2;
			}

			new_temp->data = arr[i];
			new_temp->next = NULL;
			tmp = new_temp;

			printf("Cost 1: %d\n", cost1);
			printf("Cost 2: %d\n", cost2);
			printf("Current Cost: %d\n", current_cost);
		}
		if (current_cost < best_cost)
		{
			best_cost = current_cost;
			final_cluster = head;
		}
		printf("Best Cost: %d\n", best_cost);

		first_i += 1;
	}
	first_i -= 1;

	while (second_i != 6)
	{
		k1 = arr[first_i];
		k2 = arr[second_i];
		current_cost = 0;
		C *tmp = NULL;

		for (i = 0; i < 6; i++)
		{
			cost1 = abs(k1 - arr[i]);
			cost2 = abs(k2 - arr[i]);

			C *new_temp = (C *)malloc(sizeof(C));

			if (tmp == NULL)
			{
				tmp = new_temp;
				head = tmp;
			}
			else
			{
				tmp->next = new_temp;
			}

			if (cost1 < cost2)
			{
				new_temp->label = 0;
				current_cost += cost1;
			}
			else
			{
				new_temp->label = 1;
				current_cost += cost2;
			}

			new_temp->data = arr[i];
			new_temp->next = NULL;
			tmp = new_temp;

			printf("Cost 1: %d\n", cost1);
			printf("Cost 2: %d\n", cost2);
			printf("Current Cost: %d\n", current_cost);
		}
		if (current_cost < best_cost)
		{

			best_cost = current_cost;
			final_cluster = head;
		}
		printf("Best Cost: %d\n", best_cost);
		second_i += 1;
	}

	viewCluster(final_cluster);

	return 0;
}

// initial clusters
// for (i = 0; i < k; i++){
// 	cluster[i] = coll.array[i];
// }
	
// for (p = 0; p < k; p++)
// {
// 	allMinTotalCost = 1000000;
// 	for (q = 0; q < coll.n; q++)
// 	{
// 		totalCost = 0.0;

// 		cluster[p] = coll.array[q];

// 		for (i = 0; i < coll.n; i++)
// 		{
// 			minCost = 1000000;
// 			for (j = 0; j < k; j++)
// 			{
// 				currentCost = distance(coll.array[i], cluster[j]);
// 				if (currentCost < minCost)
// 				{
// 					coll.array[i].label = j;
// 					minCost = currentCost;
// 				}
// 			}
// 			totalCost += minCost;
// 		}
// 		if (totalCost < allMinTotalCost)
// 		{
// 			allMinTotalCost = totalCost;
// 			minCostRecordIndex = q;
// 		}
// 	}
// 	cluster[p] = coll.array[minCostRecordIndex];
// }
