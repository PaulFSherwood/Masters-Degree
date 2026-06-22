#include <iostream>
#include <vector>
#include <stdexcept>

// Bubble sort function (O(n^2) time complexity)
void bubbleSort(std::vector<int>& arr) {
    size_t n = arr.size();
    if (n <= 1) return; // Already sorted if 0 or 1 element

    for (size_t i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // Optimization: stop if no swaps occurred in this pass
        if (!swapped) break;
    }
}

int main() {
    try {
        size_t size;
        std::cout << "Enter number of elements: ";
        if (!(std::cin >> size) || size > 100000) { // Limit size to avoid memory issues
            throw std::invalid_argument("Invalid size. Must be a positive integer <= 100000.");
        }

        std::vector<int> arr(size);
        std::cout << "Enter " << size << " integers:\n";
        for (size_t i = 0; i < size; ++i) {
            if (!(std::cin >> arr[i])) {
                throw std::invalid_argument("Invalid input. Please enter integers only.");
            }
        }

        bubbleSort(arr);

        std::cout << "Sorted array: ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
