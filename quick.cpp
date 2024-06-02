#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;
// Use the chrono namespace for time-related functions
using namespace std::chrono;

// Function to swap two elements
void swap(double* a, double* b) {
    double t = *a; // Temporary variable to hold the value of a
    *a = *b; // Assign the value of b to a
    *b = t; // Assign the saved value of a to b
}

// Function to partition the array on the basis of pivot
int partition (double arr[], int low, int high) {
    double pivot = arr[high];  // Pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;  // Increment index of smaller element
            swap(&arr[i], &arr[j]); // Swap current element with index
        }
    }
    swap(&arr[i + 1], &arr[high]); // Swap the pivot element with the element at (i+1)
    return (i + 1); // Return the partitioning index
}

// Function to implement Quick Sort
void quickSort(double arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1); // Before pi
        quickSort(arr, pi + 1, high); // After pi
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
    ofstream myfile ("QuickUnsortedArray.txt");
    if (myfile.is_open())
    {
        for(int i = 0; i < n; i++) {
            myfile << "arr[" << i << "] = " << arr[i] << endl; // Write each element of the array to the file
        }
        myfile.close(); // Close the file
        cout << "The unsorted array has been written to QuickUnsortedArray.txt" << endl;
    }
    else cout << "Unable to open file"; // Print an error message if the file could not be opened

    cout << "Time taken to create the array: " << duration << " milliseconds" << endl; // Print the time taken to create the array

    // Start measuring time
    t1 = high_resolution_clock::now();

    // Apply quick sort
    quickSort(arr, 0, n - 1); // Sort the array using quick sort

    // Stop measuring time and calculate the elapsed time
    t2 = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(t2 - t1).count();

    cout << "Time taken to sort the array: " << duration << " milliseconds" << endl; // Print the time taken to sort the array

    // Write the sorted array to a text file
    ofstream sortedfile ("QuickSortedArray.txt");
    if (sortedfile.is_open())
    {
        for(int i = 0; i < n; i++) {
            sortedfile << "arr[" << i << "] = " << arr[i] << endl; // Write each element of the sorted array to the file
        }
        sortedfile.close(); // Close the file
        cout << "The sorted array has been written to QuickSortedArray.txt" << endl;
    }
    else cout << "Unable to open file"; // Print an error message if the file could not be opened

    delete[] arr; // Free the memory allocated for the array

    return 0; // End of the program
}
