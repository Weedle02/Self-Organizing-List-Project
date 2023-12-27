#ifndef TRANSPOSE_H
#define TRANSPOSE_H

#include <string>
#include <vector>
#include "SelfOrderedListADT.h"
#include "llist.h"
#include "link.h"

// Template class for a Transpose self-ordering list
template <typename E>
class Transpose : public SelfOrderedListADT<E>
{
private:
    std::vector<E> Val;    // Vector to store unique values in the order they were added
    std::vector<int> Rate; // Vector to store the frequency of each corresponding value
    int compares;          // Counter for the total number of comparisons made during operations
    LList<E>* list;        // Pointer to a linked list to store the elements
public:
    // Constructor initializes the Transpose object with an empty linked list and sets the number of comparisons to zero
    Transpose() : list(new LList<E>()), compares(0) {}

    // Destructor to clean up memory used by the linked list
    ~Transpose() {}

    // Search for an element in the list, move it to the start if found, and update frequency
    bool find(const E& it)
    {
        for (int i = 0; i < Val.size(); i++)
        {
            compares++;
            if (Val[i] == it)
            {
                compares++;
                Rate[i]++;
                list->moveToStart();
                for (int b = 0; b < list->length(); b++)
                {
                    compares++;
                    if (list->getValue() == it)
                    {
                        compares++;
                        list->swapForward();  // Move the found element one position forward in the list
                        compares += 2;       // Two comparisons made during the swap operation
                    }
                    list->next();
                    compares++;
                }
                return true;  // Element found and processed
            }
        }
        add(it);  // Element not found, so add it to the list
        return false;
    }

    // Add an element to the list
    void add(const E& it)
    {
        list->append(it);      // Add the element to the linked list
        Val.push_back(it);  // Keep track of unique values in a vector
        Rate.push_back(0);     // Initialize the frequency of the added value to zero
    }

    // Get the total number of comparisons made during operations
    int getCompares() const
    {
        return compares;
    }

    // Get the size of the list (number of elements)
    int size() const
    {
        return list->length();
    }

    // Print the list with frequencies
    void printlist()
    {
        list->print(Val, Rate);
    }

    // Print the list with frequencies up to a specified limit
    void printlist(int n)
    {
        list->printAmount(Val, Rate, n);
    }


};

#endif  // TRANSPOSE_H
