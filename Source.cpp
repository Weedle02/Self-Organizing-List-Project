using namespace std;

#include "SelfOrderedListADT.h"
#include "count.h"
#include "moveToFront.h"
#include "transpose.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

// Function to print results for a given list
template <typename T>
void printListResults(SelfOrderedListADT<T>& list, const std::string& heuristicName) {
    std::cout << "\n" << heuristicName << " -"
              << " Size of list: " << list.size()
              << "\nNumber of Compares: " << list.getCompares() << std::endl;
    list.printlist();
    std::cout << std::endl;
}

int main() {
    // Initialize characters for testing
    char testChars[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
    // Input sequence for testing
    char inputChars[] = { 'F', 'D', 'F', 'G', 'E', 'G', 'F', 'A', 'D', 'F', 'G', 'E', 'H', 'I' };

    // Create instances of the self-organizing list classes
    MoveToFront<char> moveToFrontCharList;
    Transpose<char> transposeCharList;
    Count<char> countCharList;

    // Populate the lists with initial characters
    for (int i = 0; i < 8; i++) {
        countCharList.add(testChars[i]);
        moveToFrontCharList.add(testChars[i]);
        transposeCharList.add(testChars[i]);
    }

    // Test the find operation on the input sequence
    for (int i = 0; i < 14; i++) {
        countCharList.find(inputChars[i]);
        moveToFrontCharList.find(inputChars[i]);
        transposeCharList.find(inputChars[i]);
    }

    // Print results for character lists
    printListResults(countCharList, "Count Heuristic");
    printListResults(moveToFrontCharList, "Move to Front Heuristic");
    printListResults(transposeCharList, "Transpose Heuristic");
    std::cout << "\n\n\n\n";

    // Create instances of the self-organizing list classes for strings
    Count<std::string> countStringList;
    MoveToFront<std::string> moveToFrontStringList;
    Transpose<std::string> transposeStringList;

    // Open a file for string testing
    std::ifstream file;
    file.open("test.txt");

    std::string word;

    // Test the find operation on words from the file
    while (file >> word) {
        countStringList.find(word);
        moveToFrontStringList.find(word);
        transposeStringList.find(word);
    }

    file.close();

    // Print results for character lists
    printListResults(countCharList, "Count Heuristic");
    printListResults(moveToFrontCharList, "Move to Front Heuristic");
    printListResults(transposeCharList, "Transpose Heuristic");
    std::cout << "\n\n\n\n";

    return 0;
}
