#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool ArraysEqual(int *first, int *second, int length) {
    for (int i = 0; i < length; i++) {
        if (first[i] != second[i]) {
            return false;
        }
    }
    return true;
}

void PrintArray(int *array, int length) {
    printf("[");
    for (int i = 0; i < length; i++) {
        printf("%d", array[i]);

        if (i < (length - 1)) {
            printf(", ");
        }
    }

    printf("]\n");
}

int *MakeArray(int length)
{
    int *array = malloc(sizeof(int) * length);
    // NULL check here?
    return array;
}

// right is exclusive, array of [left, right)
int *MergeSortRecursive(int *array, int length, int left, int right)
{
    if ((right - left) == 1)
    {
        int *result = MakeArray(1);
        result[0] = array[left];
        return result;
    }

    int middle = (left + right) / 2;

    int leftLength = middle - left;
    int rightLength = right - middle;
    
    int *leftSide = MergeSortRecursive(array, length, left, middle);
    int *rightSide = MergeSortRecursive(array, length, middle, right);

    // Now merge the two halfs, k is index into mergedArray
    int i = 0, j = 0, k = 0;
    int *mergedArray = MakeArray(right - left);

    while (i < leftLength && j < rightLength) 
    {
        if (leftSide[i] < rightSide[j]) 
        {
            mergedArray[k++] = leftSide[i++];
        }
        else 
        {
            mergedArray[k++] = rightSide[j++];
        }
    }

    while (i < leftLength)
    {
        mergedArray[k++] = leftSide[i++];
    }
    
    while (j < rightLength)
    {
        mergedArray[k++] = rightSide[j++];
    }

    free(leftSide);
    free(rightSide);

    return mergedArray;
}

int *MergeSort(int *array, int length) 
{
    if (NULL == array || length < 1) {
        return NULL;
    }
    return MergeSortRecursive(array, length, 0, length);
}

#define ASSERT_ARR_EQ(expected, result, length) \
    if (!ArraysEqual(expected, result, length)) \
    { \
        printf("Arrays are not equal! Test on line %d\n", __LINE__); \
        printf("Expected: ");    \
        PrintArray(expected, length); \
        printf("Received: ");    \
        PrintArray(result, length); \
        exit(1);    \
    } \
    else { \
        printf("Test on line %d passes: ", __LINE__); \
        PrintArray(expected, length); \
    }

int main(void) {
    printf("Hello World\n");

    {
        int length = 1;
        int input[] = {1};
        int expected[] = {1};
        int *result = MergeSort(input, length);
        ASSERT_ARR_EQ(expected, result, length);
        free(result);
    }
    
    {
        int length = 2;
        int input[] = {1, 2};
        int expected[] = {1, 2};
        int *result = MergeSort(input, length);
        ASSERT_ARR_EQ(expected, result, length);
        free(result);
    }
    
    {
        int length = 3;
        int input[] = {1, 2, 3};
        int expected[] = {1, 2, 3};
        int *result = MergeSort(input, length);
        ASSERT_ARR_EQ(expected, result, length);
        free(result);
    }
    
    {
        int length = 4;
        int input[] = {1, 2, 3, 4};
        int expected[] = {1, 2, 3, 4};
        int *result = MergeSort(input, length);
        ASSERT_ARR_EQ(expected, result, length);
        free(result);
    }
    
    {
        int length = 4;
        int input[] = {4, 3, 2, 1};
        int expected[] = {1, 2, 3, 4};
        int *result = MergeSort(input, length);
        ASSERT_ARR_EQ(expected, result, length);
        free(result);
    }
    
    {
        int length = 4;
        int input[] = {3, 2, 4, 1};
        int expected[] = {1, 2, 3, 4};
        int *result = MergeSort(input, length);
        ASSERT_ARR_EQ(expected, result, length);
        free(result);
    }
    
    {
        int length = 4;
        int input[] = {-1, 1, 2, -2};
        int expected[] = {-2, -1, 1, 2};
        int *result = MergeSort(input, length);
        ASSERT_ARR_EQ(expected, result, length);
        free(result);
    }
    
    {
        int length = 9;
        int input[] = {1, 2, 9, 8, 5, 6, 4, 3, 7};
        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int *result = MergeSort(input, length);
        ASSERT_ARR_EQ(expected, result, length);
        free(result);
    }
    
    {
        int length = 3;
        int input[] = {1, 2, 1};
        int expected[] = {1, 1, 2};
        int *result = MergeSort(input, length);
        ASSERT_ARR_EQ(expected, result, length);
        free(result);
    }
    
    {
        int length = 3;
        int input[] = {2, 2, 1};
        int expected[] = {1, 2, 2};
        int *result = MergeSort(input, length);
        ASSERT_ARR_EQ(expected, result, length);
        free(result);
    }
    
    {
        int length = 12;
        int input[] = {-1, -8, 9, 10, 238, 5, 275, -273, 1283, 1965, 27591, -10};
        int expected[] = {-273, -10, -8, -1, 5, 9, 10, 238, 275, 1283, 1965, 27591};
        int *result = MergeSort(input, length);
        ASSERT_ARR_EQ(expected, result, length);
        free(result);
    }
    
    {
        int length = 13;
        int input[] = {57, -1, 283, 5893, 192, 5891, -9875, -8257, -95991, -5981, 5889329, 86710, 68991};
        int expected[] = {-95991, -9875, -8257, -5981, -1, 57, 192, 283, 5891, 5893, 68991, 86710, 5889329};
        int *result = MergeSort(input, length);
        ASSERT_ARR_EQ(expected, result, length);
        free(result);
    }
    return 0;
}
