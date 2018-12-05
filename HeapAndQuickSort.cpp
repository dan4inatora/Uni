#include <iostream>

using namespace std;

void makeHeap(int arr[], int size, int chosen_largest){

    int largestindex = chosen_largest;
    int left = 2 * chosen_largest + 1;
    int right = 2 * chosen_largest + 2;

    if(left < size && arr[left] > arr[largestindex]){
        largestindex = left;
    }

    if(right < size && arr[right] > arr[largestindex]){
        largestindex = right;
    }

    if(largestindex != chosen_largest){
        swap(arr[chosen_largest], arr[largestindex]);

        makeHeap(arr, size, largestindex);
    }
}

void printArr(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
}


void HeapSort(int arr[], int size){
    for(int i = size / 2 - 1; i >= 0; i--){

        makeHeap(arr, size, i);
    }

    for(int i = size - 1; i >= 0; i--){
        swap(arr[0], arr[i]);

        makeHeap(arr, i, 0);
    }
}

int pivotIndex(int arr[], int start, int end){// pivot is chosen to be last element
    int i = start - 1;

    for(int j = start; j <= end - 1; j++){

        if(arr[j] <= arr[end]){
            i++;
            swap(arr[j], arr[i]);
        }
    }
    swap(arr[i + 1], arr[end]);
    return (i + 1);
}

void quickSort(int arr[], int start, int end){

    if(start < end){

        int p_atplace = pivotIndex(arr, start, end);

        quickSort(arr, start, p_atplace - 1);
        quickSort(arr, p_atplace + 1, end);
    }
}


int main()
{
    int arr[7] = {10,2,18,3,22,31,1};
    printArr(arr, 7);
    cout<<endl;
//    HeapSort(arr, 7);
//    printArr(arr, 7);
    quickSort(arr, 0, 7);
    printArr(arr, 7);
    return 0;
}
