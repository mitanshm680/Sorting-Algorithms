#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;
// Use the chrono namespace for time-related functions
using namespace std::chrono;

// Function to perform selection sort on an array
void selectionSort(double arr[], int n) {
    int i, j, minIndex;
    double tmp;    
    // Iterate over each element of the array
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        // Find the minimum element in the unsorted part of the array
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        // Swap the found minimum element with the first element of the unsorted part
        if (minIndex != i) {
            tmp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = tmp;
        }
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
    ofstream myfile ("SelectionUnsortedArray.txt");
    if (myfile.is_open())
    {
        for(int i = 0; i < n; i++) {
            myfile << "arr[" << i << "] = " << arr[i] << endl; // Write each element of the array to the file
        }
        myfile.close(); // Close the file
        cout << "The unsorted array has been written to SelectionUnsortedArray.txt" << endl;
    }
    else cout << "Unable to open file"; // Print an error message if the file could not be opened

    cout << "Time taken to create the array: " << duration << " milliseconds" << endl; // Print the time taken to create the array

    // Start measuring time
    t1 = high_resolution_clock::now();

    // Apply selection sort
    selectionSort(arr, n); // Sort the array using selection sort

    // Stop measuring time and calculate the elapsed time
    t2 = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(t2 - t1).count();

    cout << "Time taken to sort the array: " << duration << " milliseconds" << endl; // Print the time taken to sort the array

    // Write the sorted array to a text file
    ofstream sortedfile ("SelectionSortedArray.txt");
    if (sortedfile.is_open())
    {
        for(int i = 0; i < n; i++) {
            sortedfile << "arr[" << i << "] = " << arr[i] << endl; // Write each element of the sorted array to the file
        }
        sortedfile.close(); // Close the file
        cout << "The sorted array has been written to SelectionSortedArray.txt" << endl;
    }
    else cout << "Unable to open file"; // Print an error message if the file could not be opened

    delete[] arr; // Free the memory allocated for the array

    return 0; // End of the program
}
