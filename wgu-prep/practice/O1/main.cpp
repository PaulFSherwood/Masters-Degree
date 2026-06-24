// O(1) = Constant Time: The execution time remains the same regardless of the input size.  
// Example: Accessing an element in an array by index
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Function to get an element at a specific index in O(1) time
int getElementAtIndex(const vector<int>& arr, size_t index) {
   if (index >= arr.size()) {
      throw out_of_range("Index out of range");
   }
   return arr[index]; // Direct access is O(1)
}

int main() {
   // Example vector
   vector<int> numbers = {10, 20, 30, 40, 50};

   try {
      size_t index = 3; // Access the 4th element
      int value = getElementAtIndex(numbers, index);
      cout << "Element at index " << index << " is: " << value << endl;
   }
   catch (const exception& e) {
      cerr << "Error: " << e.what() << endl;
   }

   return 0;
}
