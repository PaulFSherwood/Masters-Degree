// O(n^2) - Quadratic Time: The execution time grows quadratically with the input size.
// Example: Selection sort, where nested loops are used to sort elements.
#include <iostream>
#include <stdexcept>

// Naive recursive Fibonacci function
// Time complexity: O(2^n)
long long fibonacci(int n) {
   if (n < 0) {
      throw std::invalid_argument("Negative index not allowed");
   }
   if (n == 0) return 0;
   if (n == 1) return 1;
   return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
   int n;
   std::cout << "Enter n (<= 45 recommended): ";
   if (!(std::cin >> n) || n < 0) {
      std::cerr << "Invalid input. Please enter a non-negative integer.\n";
      return 1;
   }

   try {
      long long result = fibonacci(n);
      std::cout << "Fibonacci(" << n << ") = " << result << "\n";
   } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << "\n";
      return 1;
   }

   return 0;
}
