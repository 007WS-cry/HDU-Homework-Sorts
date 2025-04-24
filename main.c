#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>
#include "sorts.h"

// 获取当前时间（微秒）
long long getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

// 验证数组是否有序（升序）
int isSorted(long long arr[], long long n) {
    for (long long i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

// 生成随机数组（范围0~max_val）
void generateRandomArray(long long arr[], long long n, long long max_val) {
    for (long long i = 0; i < n; i++) {
        arr[i] = rand() % (max_val + 1);
    }
}

// 复制数组
void copyArray(const long long src[], long long dest[], long long n) {
    for (long long i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// 测试单个排序算法
void testSort(const wchar_t* name,
              void (*sortFunc)(long long[], long long),
              long long arr[], long long n,
              long long max_val) {
    long long* test_arr = (long long*)malloc(n * sizeof(long long));
    copyArray(arr, test_arr, n);

    long long start_time = getCurrentTime();
    sortFunc(test_arr, n);
    long long end_time = getCurrentTime();

    wprintf(L"%-12ls | 正确性: %-4ls | 耗时: %6lld μs\n",
           name,
           isSorted(test_arr, n) ? L"是" : L"否",
           end_time - start_time);

    free(test_arr);
}

// 测试需要额外参数的排序算法
void testSortWithArgs(const wchar_t* name,
                      void (*sortFunc)(long long[], long long, long long),
                      long long arr[], long long n,
                      long long max_val) {
    long long* test_arr = (long long*)malloc(n * sizeof(long long));
    copyArray(arr, test_arr, n);

    long long start_time = getCurrentTime();
    sortFunc(test_arr, n, max_val);
    long long end_time = getCurrentTime();

    wprintf(L"%-12ls | 正确性: %-4ls | 耗时: %6lld μs\n",
           name,
           isSorted(test_arr, n) ? L"是" : L"否",
           end_time - start_time);

    free(test_arr);
}

int main() {
    // 设置宽字符本地化环境
    setlocale(LC_ALL, "");

    srand(time(NULL));  // 初始化随机种子

    // 测试规模数组
    long long sizes[] = {100, 1000, 10000, 100000, 1000000};
    long long max_val = 10000;  // 桶排序的最大值

    for (int i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        long long n = sizes[i];
        long long* arr = (long long*)malloc(n * sizeof(long long));
        generateRandomArray(arr, n, max_val);

        wprintf(L"\n===== 数据规模: %lld =====\n", n);

        // 对于小规模数据（<100000）测试O(n²)算法
        if (n < 100000) {
            testSort(L"冒泡排序", bubbleSort, arr, n, max_val);
            testSort(L"选择排序", selectionSort, arr, n, max_val);
            testSort(L"插入排序", insertionSort, arr, n, max_val);
        } else {
            wprintf(L"跳过O(n²)排序算法（冒泡/选择/插入）\n");
        }

        // 测试O(n log n)和O(n)算法
        // 快速排序需要包装
        long long* quick_arr = (long long*)malloc(n * sizeof(long long));
        copyArray(arr, quick_arr, n);
        long long start_time = getCurrentTime();
        quickSort(quick_arr, 0, n-1);
        long long end_time = getCurrentTime();
        wprintf(L"%-12ls | 正确性: %-4ls | 耗时: %6lld μs\n",
               L"快速排序", isSorted(quick_arr, n) ? L"是" : L"否", end_time - start_time);
        free(quick_arr);

        // 归并排序需要包装
        long long* merge_arr = malloc(n * sizeof(long long));
        copyArray(arr, merge_arr, n);
        start_time = getCurrentTime();
        mergeSort(merge_arr, 0, n-1);
        end_time = getCurrentTime();
        wprintf(L"%-12ls | 正确性: %-4ls | 耗时: %6lld μs\n",
               L"归并排序", isSorted(merge_arr, n) ? L"是" : L"否", end_time - start_time);
        free(merge_arr);

        testSort(L"希尔排序", shellSort, arr, n, max_val);
        testSortWithArgs(L"桶排序", bucketSort, arr, n, max_val);
        testSort(L"计数排序", countingSort, arr, n, max_val);
        testSort(L"堆排序", heapSort, arr, n, max_val);

        free(arr);
    }
    system("pause");

    return 0;
}