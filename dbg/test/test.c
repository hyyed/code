#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void InitArr(int arr[], int len, int start, int end); //初始化
void ShowArr(int arr[], int len); //显示数组
void QuickSort(int arr[], int left, int right); //快速排序
int  Partition(int arr[], int left, int right); //块排序
void ReverseArr(int arr[], int len); //逆转数组

int main()
{
    int a = 10;
    int arr[a];
    InitArr(arr, a, 1, 10*a);
    ShowArr(arr, a);

    QuickSort(arr, 0, a-1);
    ShowArr(arr, a);

    ReverseArr(arr,a);
    ShowArr(arr, a);

    return 0;
}

void InitArr(int arr[], int len, int start, int end) {
    for (int i = 0; i < len; i++) {
        arr[i] = rand()%(end - start) + start;;
    }
    printf("初始化成功！\n");
}

void ShowArr(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
}

int Partition(int arr[], int left, int right)  {
    int pivot = arr[left];  // 第一个数作为基准
    while (left < right)
    {
        while (left < right && arr[right] >= pivot) --right; //遍历右边，直到遇到比基准小的
        arr[left] = arr[right];             //右边小的移到左边
        while (left < right && arr[left] <= pivot) ++left; 
        arr[right] = arr[left];
    }
    arr[left] = pivot;  //将基准数插入到左右相等位置
    return left;        //返回左右相等的地址
}

void QuickSort(int arr[], int left, int right) {
    if (left < right) {
        int pivot = Partition(arr, left, right);
        QuickSort(arr, left, pivot - 1);
        QuickSort(arr, pivot + 1, right);
    }
}

void ReverseArr(int arr[], int len) {
    int carr[len];
    for (int i=0; i<len; ++i) {
        carr[len-i-1] = arr[i];
    }
    for (int i=0; i<len; ++i) {
        arr[i] = carr[i];
    }
}