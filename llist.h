#ifndef LLIST_H
#define LLIST_H

#include <vector>
#include "SelfOrderedListADT.h"
#include "link.h"
#include "list.h"
#include "book.h"
#include <memory>

// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This is the file to include in your code if you want access to the
// complete LList template class

// This is the declaration for LList. It is split into two parts
// because it is too big to fit on one book page
// Linked list implementation

template <typename E>
class LList : public List<E>
{
public:
    // Constructor
    LList() { init(); }

    // Destructor
    ~LList() { removeall(); }

    // Print elements in the linked list based on vectors v and f
    void print(std::vector<E> v, std::vector<int> f) {
        current_0= hd;
        int count_0 = 0;

        while (count_0 < count_1) {
            for (int n = 0; n < count_1; n++) {
                if (v[n] == current_0->element) {
                    std::cout << current_0->element << "-" << f[n] << " ";
                    next();
                    count_0++;
                }
            }
        }
    }

    // Print a specified amount of elements in the linked list based on vectors v and f
    void printAmount(std::vector<E> v, std::vector<int> f, int amtt) {
        if (amtt > count_1) {
            amtt = count_1;
        }

        current_0= hd;
        int count_0 = 0;

        while (true) {
            for (int n = 0; n < count_1; n++) {
                if (v[n] == current_0->element) {
                    std::cout << current_0->element << "-" << f[n] << " ";
                    count_0++;
                    next();
                }
                if (count_0 == amtt) {
                    return;
                }
            }
        }
    }

    // Clear the linked list
    void clear() { removeall(); init(); }

    // Insert a new element into the linked list
    void insert(const E& it) {
        // Save the current node's next pointer in a temporary variable
        auto tempNext = current_0->next;

        // Create a new Link node with the given data and update current node's next pointer
        current_0->next = new Link<E>{it, current_0->next};

        // Update the tl pointer if the current node is the tl
        tl = (tl == current_0) ? current_0->next : tl;

        // Move the current node pointer to the newly inserted node
        current_0= current_0->next;

        // Update the next pointer of the newly inserted node to the saved next pointer
        current_0->next = tempNext;

        // Increment the count_0 of elements in the list
        ++count_1;
    }

    // Append a new element to the end of the linked list
    void append(const E& it)
    {
        tl = tl->next = new Link<E>(it, nullptr);
        if (count_1 == 0)
        {
            sethd(tl);
        }
        count_1++;
    }

    // Remove and return the current element in the linked list
    E remove() {
        // Ensure that there is an element to remove
        Assert(current_0->next != nullptr, "No element");

        // Save the element of the node to be removed
        E it = current_0->next->element;

        // Save the next pointer of the node to be removed
        Link<E>* ltemp = current_0->next;

        // Update the tl pointer if the node to be removed is the tl
        if (tl == current_0->next) 
            tl = current_0;

        // Update the next pointer of the current node to skip the node to be removed
        current_0->next = current_0->next->next;

        // Delete the node to be removed
        delete ltemp;

        // Decrement the count_0 of elements in the list
        --count_1;

        // Return the removed element
        return it;
    }

    // Move the current position to the start of the linked list
    void moveToStart()
    {
        current_0= hd;
    }

    // Move the current position to the end of the linked list
    void moveToEnd()
    {
        current_0= tl;
    }

    // Move the current position to the previous node in the linked list
    void prev()
    {
        if (current_0== hd) return;
        Link<E>* temp = hd;
        while (temp->next != current_0) temp = temp->next;
        current_0= temp;
    }

    // Move the current position to the next node in the linked list
    void next()
    {
        if (current_0!= tl) current_0= current_0->next;
    }

    // Return the length (number of elements) in the linked list
    int length() const { return count_1; }

    // Return the current position in the linked list
    int currPos() const
    {
        Link<E>* temp = hd;
        int i;
        for (i = 0; current_0!= temp; i++)
            temp = temp->next;
        return i;
    }

    // Move the current position to a specified position in the linked list
    void moveToPos(int pos)
    {
        Assert((pos >= 0) && (pos <= count_1), "Position out of range");
        current_0= hd;
        for (int i = 0; i < pos; i++) current_0= current_0->next;
    }

    // Return the value of the current element in the linked list
    const E& getValue() const
    {
        Assert(current_0!= nullptr, "No value");
        return current_0->element;
    }

    // Return the value of the previous element in the linked list
    E getPrev()
    {
        prev();
        E tempReturn = current_0->element;
        next();
        return tempReturn;
    }

    // Set the hd of the linked list to a specified link
    void sethd(Link<E>* link)
    {
        hd = link;
    }

    // Swap the current node with the next node in the linked list
    void swapForward() {
        // Save the current and next nodes in temporary variables
        Link<E>* tempcurrent_0= current_0;
        Link<E>* tempNext = current_0->next;

        // Move to the previous node
        prev();
        Link<E>* tempPrev = current_0;

        // Move to the node before the previous one
        prev();

        // Check if the hd is not the node before the previous one
        if (hd != tempPrev) {
            // Update the next pointer of the current node to skip the next node
            current_0->next = current_0->next->next;
        } else {
            // Update the hd pointer if the node before the previous one is the hd
            hd = tempcurrent_0;
        }

        // Reset the current node
        current_0= tempcurrent_0;

        // Update the next pointer of the current node to the previous node
        current_0->next = tempPrev;

        // Check if the current node is not the tl
        if (tempcurrent_0 != tl) {
            // Update the next pointer of the previous node to the next node
            tempPrev->next = tempNext;
        } else {
            // Update the tl pointer and add a new Link node if the current node is the tl
            tl = tempcurrent_0->next;
            tl->next = new Link<E>();
        }
    }

    // Swap the current node with the hd of the linked list
    void swapFirst() {
        // Check if the current node is not the hd
        if (current_0!= hd) {
            // Save the current node in a temporary variable
            Link<E>* tempcurrent_0= current_0;

            // Move to the previous node
            prev();

            // Check if the temporary node is not the tl
            if (tempcurrent_0 != tl) {
                // Update the next pointer of the current node to skip the temporary node
                current_0->next = current_0->next->next;
            } else {
                // Update the tl pointer and add a new Link node if the temporary node is the tl
                tl = current_0;
                tl->next = new Link<E>;
            }

            // Update the next pointer of the temporary node to point to the hd
            tempcurrent_0->next = hd;

            // Update the hd pointer to the temporary node
            hd = tempcurrent_0;
        }
    }

private:
    // Pointer to the hd of the linked list
    // Pointer to the tl of the linked list
    // Pointer to the current position in the linked list
    // count_0er to keep track of the number of elements in the list
    Link<E>* hd;
    Link<E>* tl;
    Link<E>* current_0;
    int count_1;

    // Initialize the linked list
    void init() {
        hd = tl = current_0 = new Link<E>;
        count_1 = 0;
    }

    // Remove all nodes in the linked list
    void removeall() {
        delete hd;
        hd = tl = current_0 = nullptr;
        count_1 = 0;
    }
};

#endif
