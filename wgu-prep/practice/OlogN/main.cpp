// O(log n) - Logarithmic Time: The execution time grows logarithmically as the input size increases.
// Example: Binary search
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm> // for sort

// Binary search function: O(log n) time complexity
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;

    while (left <= right) {
        // Prevent integer overflow in mid calculation
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid; // Found target
        }
        else if (arr[mid] < target) {
            left = mid + 1; // Search right half
        }
        else {
            right = mid - 1; // Search left half
        }
    }
    return -1; // Not found
}

int main() {
    try {
        int n;
        std::cout << "Enter number of elements: ";
        if (!(std::cin >> n) || n <= 0) {
            throw std::invalid_argument("Invalid size. Must be a positive integer.");
        }

        std::vector<int> data(n);
        std::cout << "Enter " << n << " integers (unsorted): ";
        for (int i = 0; i < n; ++i) {
            if (!(std::cin >> data[i])) {
                throw std::invalid_argument("Invalid input. Please enter integers only.");
            }
        }

        // Sort array before binary search
        std::sort(data.begin(), data.end());

        int target;
        std::cout << "Enter number to search: ";
        if (!(std::cin >> target)) {
            throw std::invalid_argument("Invalid input. Please enter an integer.");
        }

        int index = binarySearch(data, target);

        if (index != -1) {
            std::cout << "Found " << target << " at index " << index << " (0-based index).\n";
        } else {
            std::cout << target << " not found in the array.\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
