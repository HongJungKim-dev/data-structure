#include <stdio.h>
#include "Usefulheap.h"

int PriComp(int n1, int n2);
void HeapSort(int arr[], int n, PriorityComp pc);

int main()
{
    int arr[4] = {3, 4, 2, 1};
    int i = 0;

    HeapSort(arr, sizeof(arr) / sizeof(int), PriComp);

    for (i = 0; i < 4; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int PriComp(int n1, int n2)
{
    return n2 - n1;
}

void HeapSort(int arr[], int n, PriorityComp pc)
{
    Heap heap;
    int i = 0;

    //초기화
    HeapInit(&heap, pc);

    //삽입
    for (i = 0; i < n; i++)
    {
        HInsert(&heap, arr[i]);
    }

    //삭제
    for (i = 0; i < n; i++)
    {
        arr[i] = HDelete(&heap);
    }
}