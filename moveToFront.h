#ifndef MOVETOFRONT_H
#define MOVETOFRONT_H

#include <string>
#include <vector>
#include "SelfOrderedListADT.h"
#include "llist.h"
#include "link.h"

// Template class for Move-to-Front self-ordered list algorithm
template <typename E>
class MoveToFront : public SelfOrderedListADT<E>
{
public:
    // Constructor: Initializes the MoveToFront object with an empty linked list and zero compares
    MoveToFront() : list(new LList<E>()), compares(0) {}

    // Destructor: Releases memory allocated for the linked list
    ~MoveToFront() {
        delete list;
    }

    // Search for an element in the self-ordered list
    bool find(const E& elem_1)
    {
        // Loop through the stored values to find the element
        for (int i = 0; i < elem_2.size(); i++)
        {
            compares++;
            // If the element is found, increment valfreq, move elem_1 to the front, and return true
            if (elem_2[i] == elem_1)
            {
                compares++;
                valfreq[i]++;
                moveToStart(elem_1);
                return true;
            }
        }

        // If the element is not found, add elem_1 to the list and return false
        add(elem_1);
        compares += 2;
        return false;
    }

    // Add an element to the self-ordered list
    void add(const E& elem_1)
    {
        // Insert the element into the linked list, move elem_1 to the front, and update vectors
        list->insert(elem_1);
        list->swapFirst();
        elem_2.push_back(elem_1);
        valfreq.push_back(0);
    }

    // Get the total number of compares made during find operations
    int getCompares() const
    {
        return compares;
    }

    // Get the current size of the self-ordered list
    int size() const
    {
        return list->length();
    }

    // Print the elements of the self-ordered list along with their frequencies
    void printlist()
    {
        list->print(elem_2, valfreq);
    }

    // Print the first 'n' elements of the self-ordered list along with their frequencies
    void printlist(int n)
    {
        list->printAmount(elem_2, valfreq, n);
    }

private:
    // Private member variables
    int compares;      // Count of compares made during find operations
    LList<E>* list;    // Pointer to the linked list
    std::vector<E> elem_2;  // Vector to store distinct values in the list
    std::vector<int> valfreq;  // Vector to store the frequency of each corresponding value

    // Move the specified element to the start of the linked list
    void moveToStart(const E& elem_1)
    {
        bool fin = false;
        list->moveToStart();
        while (!fin)
        {
            // If the element is found in the list, swap elem_1to the front and exelem_1the loop
            if (list->getValue() == elem_1)
            {
                compares++;
                list->swapFirst();
                compares += 2;
                fin = true;
                return;
            }
            list->next();
        }
    }
};

#endif
