#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;
// Use the chrono namespace for time-related functions
using namespace std::chrono;

// Function to merge two subarrays
void merge(double arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1; // Calculate the size of the first subarray
    int n2 = right - mid; // Calculate the size of the second subarray

    // Create temp arrays
    vector<double> L(n1), R(n2); // Create two temporary vectors to hold the subarrays

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i]; // Copy the first subarray into L
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j]; // Copy the second subarray into R

    // Merge the temp arrays back into arr[left..right]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { // If the current element of L is smaller or equal to the current element of R
            arr[k] = L[i]; // Copy the element from L into the merged array
            i++; // Move to the next element in L
        } else {
            arr[k] = R[j]; // Copy the element from R into the merged array
            j++; // Move to the next element in R
        }
        k++; // Move to the next position in the merged array
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i]; // Copy the remaining elements from L into the merged array
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j]; // Copy the remaining elements from R into the merged array
        j++;
        k++;
    }
}

// Function to implement merge sort
void mergeSort(double arr[], int left, int right) {
    if (left < right) { // If the left index is less than the right index, there's more than one element in the subarray
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2; // Calculate the middle index of the subarray

        // Sort first and second halves
        mergeSort(arr, left, mid); // Recursively sort the first half
        mergeSort(arr, mid + 1, right); // Recursively sort the second half

        merge(arr, left, mid, right); // Merge the two sorted halves
    }
}


int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator with the current time

    int n; // Declare a variable to hold the size of the array
    cout << "Enter the size of the array: ";
    cin >> n; // Read the size of the array from the user

    double* arr = new double[n]; // Dynamically allocate an array of size n

    // Start measuring time
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    for(int i = 0; i < n; i++) {
        // Generate random double between 100.00 and 1000.00
        arr[i] = 100.00 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX/(1000.00-100.00)));
    }

    // Stop measuring time and calculate the elapsed time
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();

    // Write the unsorted array to a text file
    ofstream myfile ("MergeUnsortedArray.txt");
    if (myfile.is_open())
    {
        for(int i = 0; i < n; i++) {
            myfile << "arr[" << i << "] = " << arr[i] << endl; // Write each element of the array to the file
        }
        myfile.close(); // Close the file
        cout << "The unsorted array has been written to MergeUnsortedArray.txt" << endl;
    }
    else cout << "Unable to open file"; // Print an error message if the file could not be opened

    cout << "Time taken to create the array: " << duration << " milliseconds" << endl; // Print the time taken to create the array

    // Start measuring time
    t1 = high_resolution_clock::now();

    // Apply merge sort
    mergeSort(arr, 0, n - 1); // Sort the array using merge sort

    // Stop measuring time and calculate the elapsed time
    t2 = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(t2 - t1).count();

    cout << "Time taken to sort the array: " << duration << " milliseconds" << endl; // Print the time taken to sort the array

    // Write the sorted array to a text file
    ofstream sortedfile ("MergeSortedArray.txt");
    if (sortedfile.is_open())
    {
        for(int i = 0; i < n; i++) {
            sortedfile << "arr[" << i << "] = " << arr[i] << endl; // Write each element of the sorted array to the file
        }
        sortedfile.close(); // Close the file
        cout << "The sorted array has been written to MergeSortedArray.txt" << endl;
    }
    else cout << "Unable to open file"; // Print an error message if the file could not be opened

    delete[] arr; // Free the memory allocated for the array

    return 0; // End of the program
}
