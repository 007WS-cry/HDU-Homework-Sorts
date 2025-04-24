//
// Created by lenovo on 2025/4/24.
//

#ifndef SORTS_H
#define SORTS_H

void bubbleSort(long long arr[], long long n);
void selectionSort(long long arr[], long long n);
void insertionSort(long long arr[], long long n);
long long partition(long long arr[], long long low, long long high);
void quickSort(long long arr[], long long l, long long r);
void merge(long long arr[], long long l, long long m, long long r);
void mergeSort(long long arr[], long long l, long long r);
void shellSort(long long arr[], long long n);
void heapify(long long arr[], long long n, long long i);
void countingSort(long long arr[], long long n);
void heapSort(long long arr[], long long n);
void bucketSort(long long arr[], long long n, const long long MAX_VALUE);

#endif //SORTS_H
