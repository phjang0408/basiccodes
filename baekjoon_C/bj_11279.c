#include <stdio.h>

#define MAX_CAPACITY 100001

int size = 1;
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void heapify(int heap[], int i)
{
    int largest = i;
    int left = 2 * i, right = 2 * i + 1;
    if (heap[largest] < heap[left] && left < size)
    {
        largest = left;
    }
    if (heap[largest] < heap[right] && right < size)
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(&heap[largest], &heap[i]);
        heapify(heap, largest);
    }
}

void insert(int heap[], int value)
{
    heap[size++] = value;
    int i = size - 1;
    while (i > 1 && heap[i] > heap[i / 2])
    {
        swap(&heap[i / 2], &heap[i]);
        i = i / 2;
    }
}

int Extract(int heap[])
{
    if (size == 1)
    {
        return 0;
    }
    int mx = heap[1];
    heap[1] = heap[--size];
    heapify(heap, 1);

    return mx;
}

int main()
{
    int N, cmd, i;
    int heap[MAX_CAPACITY];
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d", &cmd);
        if (cmd == 0)
        {
            printf("%d\n", Extract(heap));
        }
        else
        {
            insert(heap, cmd);
        }
    }
}