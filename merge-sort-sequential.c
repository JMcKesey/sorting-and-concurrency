#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define g_SIZE 50000000

void randomArray(int *arr, int size)
{
	srand(time(NULL));
	for(int i=0; i < size; ++i) {
		arr[i] = rand() % 10000000;
	}
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int left_half_count = m - l + 1;
	int right_half_count = r - m;

	int *L = malloc(left_half_count * sizeof(int));
	int *R = malloc(right_half_count * sizeof(int));

	if (L == NULL || R == NULL)
	{
		fprintf(stderr, "Memory allocation failed in merge\n");
		exit(EXIT_FAILURE);
	}

	for(i=0; i<left_half_count; i++)
	{
		L[i] = arr[l + i];
	}
	for(j=0; j<right_half_count; j++)
	{
		R[j] = arr[m + 1 + j];
	}

	i=0; j=0; k=l;
	while(i < left_half_count && j < right_half_count)
	{
		if(L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while(i < left_half_count)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while(j < right_half_count)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	free(L);
	free(R);
}

void merge_sort(int arr[], int l, int r)
{
	if(l < r)
	{
		int m = l + (r - l) / 2;

		merge_sort(arr, l, m);
		merge_sort(arr, m+1, r);

		merge(arr, l, m, r);
	}
}


int main()
{
	int *arr = malloc(g_SIZE * sizeof(int));
	if(arr == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return EXIT_FAILURE;
	}
	randomArray(arr, g_SIZE);

	clock_t begin = clock();
	merge_sort(arr, 0, g_SIZE-1);
	clock_t end = clock();

	double time_elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Elapsed time %f seconds\n", time_elapsed);
	// int i;
	// for(i=0; i<g_SIZE; i++)
	// {
	// 	printf("%d\n", arr[i]);
	// }

	return 0;
}
