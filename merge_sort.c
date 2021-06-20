#include <stdio.h>
#include <stdlib.h>

void MergeTwoArea(int arr[], int left, int mid, int right);
void MergeSort(int arr[], int left, int right);

int main()
{
    int arr[7] = {3, 2, 4, 1, 7, 6, 5};
    int i = 0;
    int arr_len = sizeof(arr) / sizeof(int);
    MergeSort(arr, 0, arr_len - 1);

    for (i = 0; i < 7; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void MergeTwoArea(int arr[], int left, int mid, int right)
{
    int fIdx = left;
    int rIdx = mid + 1;
    int i = 0;

    int *sortArr = (int *)malloc(sizeof(int) * (right + 1));
    int sIdx = left;

    while (fIdx <= mid && rIdx <= right)
    {
        if (arr[fIdx] >= arr[rIdx])
        {
            sortArr[sIdx] = arr[rIdx++];
        }
        else if (arr[fIdx] < arr[rIdx])
        {
            sortArr[sIdx] = arr[fIdx++];
        }
        sIdx++;
    }

    if (fIdx > mid)
    {
        for (i = rIdx; i <= right; i++, sIdx++)
        {
            sortArr[sIdx] = arr[i];
        }
    }
    else
    {
        for (i = fIdx; i <= mid; i++, sIdx++)
        {
            sortArr[sIdx] = arr[i];
        }
    }

    for (i = left; i <= right; i++)
    {
        arr[i] = sortArr[i];
    }

    free(sortArr);
}

void MergeSort(int arr[], int left, int right)
{
    int mid = 0;

    if (left < right)
    {
        //중간지점 계산
        mid = (left + right) / 2;
        //둘로 나눠서 각각 정렬
        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);

        //정렬된 두 배열 병합
        MergeTwoArea(arr, left, mid, right);
    }
}
