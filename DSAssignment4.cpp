#include <iostream>
using namespace std;

// Function to merge two sorted subarrays into one
void merge(int arr[], int start, int mid, int end) {
    int size1 = mid - start + 1;
    int size2 = end - mid;

    int* left = new int[size1];
    int* right = new int[size2];

    // Copy data to temporary arrays
    for(int i = 0; i < size1; i++)
        left[i] = arr[start + i];
    for(int j = 0; j < size2; j++)
        right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = start;

    // Merge the temp arrays back into original array
    while(i < size1 && j < size2) {
        if(left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // Copy remaining elements (if any)
    while(i < size1)
        arr[k++] = left[i++];
    while(j < size2)
        arr[k++] = right[j++];

    delete[] left;
    delete[] right;
}

// Recursive Merge Sort function
void mergeSort(int arr[], int start, int end) {
    if(start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

// Main function to test the merge sort
int main() {
    int arr[11] = {38, 27, 43, 3, 9, 82, 10, 5, 7, 6, 12};

    cout << "Original Array: ";
    for(int i = 0; i < 11; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    mergeSort(arr, 0, 10);

    cout << "Sorted Array: ";
    for(int i = 0; i < 11; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
