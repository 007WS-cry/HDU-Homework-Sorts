//
// Created by lenovo on 2025/4/24.
//

#include "sorts.h"

#include <stdio.h>
#include <stdlib.h>

// 冒泡排序
void bubbleSort(long long arr[], long long n) {
    for (long long i = 0; i < n-1; i++) {
        for (long long j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // 交换
                long long temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// 选择排序
void selectionSort(long long arr[], long long n) {
    for (long long i = 0; i < n-1; i++) {
        long long min_idx = i;
        for (long long j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // 交换
        long long temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

// 插入排序
void insertionSort(long long arr[], long long n) {
    for (long long i = 1; i < n; i++) {
        long long key = arr[i];
        long long j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// 快速排序的辅助函数 - 分区
long long partition(long long arr[], long long low, long long high) {
    long long pivot = arr[high];
    long long i = low - 1;

    for (long long j = low; j <= high-1; j++) {
        if (arr[j] < pivot) {
            i++;
            // 交换
            long long temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // 交换pivot到正确位置
    long long temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return i+1;
}

// 快速排序
void quickSort(long long arr[], long long low, long long high) {
    if (low < high) {
        long long pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

// 归并排序的辅助函数 - 合并（保持不变）
void merge(long long arr[], long long l, long long m, long long r) {
    long long n1 = m - l + 1;
    long long n2 = r - m;

    long long *L = (long long *)malloc(n1 * sizeof(long long));
    long long *R = (long long *)malloc(n2 * sizeof(long long));

    for (long long i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (long long j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    long long i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// 迭代版归并排序（解决栈溢出）
void mergeSort(long long arr[], long long l, long long r) {
    if (l >= r) return;

    long long n = r - l + 1;
    // 当前子数组大小 (1, 2, 4, 8...)
    // 子数组起始位置

    // 自底向上迭代
    for (long long curr_size = 1; curr_size <= n-1; curr_size = 2*curr_size) {
        for (long long left_start = l; left_start < n; left_start += 2*curr_size) {
            long long mid = left_start + curr_size - 1;
            if (mid >= n) mid = n - 1;

            long long right_end = left_start + 2*curr_size - 1;
            if (right_end >= n) right_end = n - 1;

            merge(arr, left_start, mid, right_end);
        }
    }
}

// 希尔排序
void shellSort(long long arr[], long long n) {
    for (long long gap = n/2; gap > 0; gap /= 2) {
        for (long long i = gap; i < n; i++) {
            long long temp = arr[i];
            long long j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// 计数排序
void countingSort(long long arr[], long long n) {
    // 找到数组中的最大值
    long long max = arr[0];
    for (long long i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // 创建计数数组并初始化
    long long *count = (long long *)calloc(max + 1, sizeof(long long));

    // 统计每个元素出现的次数
    for (long long i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // 计算前缀和
    for (long long i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // 创建临时数组存储排序结果
    long long *output = (long long *)malloc(n * sizeof(long long));

    // 从后往前遍历原数组，保证稳定性
    for (long long i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // 将结果复制回原数组
    for (long long i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

// 堆排序的辅助函数 - 堆调整
void heapify(long long arr[], long long n, long long i) {
    long long largest = i;        // 初始化最大元素为根节点
    long long left = 2 * i + 1;   // 左子节点
    long long right = 2 * i + 2;  // 右子节点

    // 如果左子节点大于根节点
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // 如果右子节点大于当前最大节点
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // 如果最大元素不是根节点
    if (largest != i) {
        // 交换
        long long temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // 递归调整受影响的子树
        heapify(arr, n, largest);
    }
}

// 堆排序
void heapSort(long long arr[], long long n) {
    // 构建最大堆（从最后一个非叶子节点开始）
    for (long long i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 逐个提取元素
    for (long long i = n - 1; i > 0; i--) {
        // 将当前根节点（最大值）移动到数组末尾
        long long temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // 调整剩余元素组成的堆
        heapify(arr, i, 0);
    }
}

// 桶排序
void bucketSort(long long arr[], long long n, const long long MAX_VALUE) {
    long long *buckets = calloc(MAX_VALUE + 1, sizeof(long long));

    // 计数
    for (long long i = 0; i < n; i++) {
        buckets[arr[i]]++;
    }

    // 重新填充原数组
    long long index = 0;
    for (long long i = 0; i <= MAX_VALUE; i++) {
        while (buckets[i] > 0) {
            arr[index++] = i;
            buckets[i]--;
        }
    }

    free(buckets);
}