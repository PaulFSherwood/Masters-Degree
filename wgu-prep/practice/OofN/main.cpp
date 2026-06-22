// O(n) - Linear Time: The execution time grows linearly with the input size.
// Example: A simple loop through an array
#include <iostream>
#include <vector>
#include <stdexcept> // For exception handling

// Function to compute sum of elements in O(n) time
long long sumArray(const std::vector<int>& arr) {
    long long sum = 0; // Use long long to avoid overflow for large sums
    for (int num : arr) {
        sum += num;
    }
    return sum;
}

int main() {
    int n;
    std::cout << "Enter number of elements: ";

    // Input validation
    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Invalid input. Please enter a non-negative integer.\n";
        return 1;
    }

    std::vector<int> arr(n);
    std::cout << "Enter " << n << " integers:\n";

    for (int i = 0; i < n; ++i) {
        if (!(std::cin >> arr[i])) {
            std::cerr << "Invalid input. Please enter integers only.\n";
            return 1;
        }
    }

    // Compute sum in O(n) time
    long long result = sumArray(arr);

    std::cout << "Sum of elements: " << result << "\n";
    return 0;
}
