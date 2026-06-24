#include <iostream>
#include <string>

// Utility function to print indentation based on call depth
void printIndent(int depth) {
    for (int i = 0; i < depth; ++i) {
        std::cout << "  "; // two spaces per depth level
    }
}

// Function C
void functionC(int depth) {
    printIndent(depth);
    std::cout << "Entering functionC\n";

    // Simulate some work
    printIndent(depth);
    std::cout << "functionC is doing work...\n";

    printIndent(depth);
    std::cout << "Leaving functionC\n";
}

// Function B
void functionB(int depth) {
    printIndent(depth);
    std::cout << "Entering functionB\n";

    functionC(depth + 1); // Call next function

    printIndent(depth);
    std::cout << "Leaving functionB\n";
}

// Function A
void functionA(int depth) {
    printIndent(depth);
    std::cout << "Entering functionA\n";

    functionB(depth + 1); // Call next function

    printIndent(depth);
    std::cout << "Leaving functionA\n";
}

int main() {
    std::cout << "Program started\n";

    functionA(1); // Start the chain of calls

    std::cout << "Program ended\n";
    return 0;
}
