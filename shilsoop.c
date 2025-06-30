#include <stdio.h>

void sub_shell_sort(int *list, int left, int right, int gap)
{
    int i, j, k;
    for (i = left + gap; i < right; i += gap)
    {
        int key = list[i];
        for(j = i - gap; j >= left && key < list[j]; j-=gap){
            list[j + gap] = list[j];
        }
        list[j + gap] = key;
    }
}

void shell_sort(int *list, int size)
{
    int gap;
    for (gap = (size) / 2; gap > 0; gap /= 2)
    {
        if (gap % 2 == 0)
            gap += 1;
        if (gap == 0)
            gap = 1;
        for (int i = 0; i < gap; i++)
        {
            sub_shell_sort(list, i, size, gap);
        }
    }
}
int main()
{
    int list[10] = {1, 4, 3, 6, 5, 2, 7, 8, 9, 0};

    // 원래 배열 출력
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", list[i]);
    }
    printf("\n");

    shell_sort(list, 10);

    // 정렬된 배열 출력
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", list[i]);
    }
}