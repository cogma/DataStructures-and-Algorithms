#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define N 4000000

int heap[N + 1];
int heap_last = 0;

void swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void insert(int heap[], int object)
{
	int i;

	heap[heap_last] = object;

	i = heap_last;
	while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
		swap(heap, i, (i - 1) / 2);
		i = (i - 1) / 2;
	}
}

void deletemin(int heap[])
{
	int i = 0;
	int object = 0;

	object = heap[0];

	heap[0] = heap[heap_last];
	heap[heap_last] = RAND_MAX ;

	while (i < heap_last / 2 && (heap[i] > heap[2 * i + 1] || heap[i] > heap[2 * i + 2])) {
		if (heap[i] > heap[2 * i + 1]) {
			if (heap[2 * i + 2] >= heap[2 * i + 1]) {
				swap(heap, i, 2 * i + 1);
				i = 2 * i + 1;
			}
			else {
				swap(heap, i, 2 * i + 2);
				i = 2 * i + 2;
			}
		}
		else if (heap[i] > heap[2 * i + 2]) {
			swap(heap, i, 2 * i + 2);
			i = 2 * i + 2;
		}
	}
}

int main(void)
{
	int i;

	srand((unsigned)time(NULL));

	clock_t start = clock();

	for (i = 0; i < N; i++) {
		insert(heap, rand());
		heap_last++;
	}
	insert(heap, RAND_MAX + 1);

	heap_last--;

	for (i = 0; i < N; i++) {
		deletemin(heap);
		heap_last--;
	}

	clock_t end = clock();

	printf("%f msec.\n", (double)(end - start)/CLOCKS_PER_SEC*1000);

}
