#ifndef COUNT_H
#define COUNT_H

#include <string>
#include <vector>
#include "SelfOrderedListADT.h"
#include "llist.h"
#include "link.h"

template <typename E>
class Count : public SelfOrderedListADT<E>
{
public:
    Count() : compares(0), list(new LList<E>()) {}

    ~Count() {
        delete list;
    }

    // Find the element in the list and update frequency
    bool find(const E& elem_0)
    {
        for (int i = 0; i < dVal.size(); i++)
        {
            compares++;
            if (dVal[i] == elem_0)
            {
                compares++;
                valfreq[i]++;
                moveToCorrectPosition(elem_0, i);
                return true;
            }
        }

        // If the element is not found, add elem_0 to the list
        add(elem_0);
        return false;
    }

    // Add an element to the list without sorting
    void add(const E& elem_0)
    {
        list->append(elem_0);
        dVal.push_back(elem_0);
        valfreq.push_back(0);
    }

    // Return the amount of comparisons made
    int getCompares() const
    {
        return compares;
    }

    // Return the size of the list
    int size() const
    {
        return list->length();
    }

    // Print the entire list with frequencies
    void printlist()
    {
        list->print(dVal, valfreq);
    }

    // Print the list up to the specified amount
    void printlist(int n)
    {
        list->printAmount(dVal, valfreq, n);
    }

private:
    int compares;
    LList<E>* list;
    std::vector<E> dVal; // Remembers the values contained in the list and corresponds to the frequency
    std::vector<int> valfreq;  // Remembers the frequency of each value

    // Move the element to its correct position in the list based on frequency
    void moveToCorrectPosition(const E& elem_0, int index)
    {
        list->moveToStart();
        for (int b = 0; b < list->length(); b++)
        {
            compares++;

            if (list->getValue() == elem_0)
            {
                compares++;
                bool fin = false;

                while (!fin)
                {
                    compares++;

                    for (int n = 0; n < dVal.size(); n++)
                    {
                        compares++;
                        if (list->getPrev() == dVal[n])
                        {
                            compares++;
                            if (valfreq[n] < valfreq[index])
                            {
                                compares++;
                                list->swapForward();
                                compares += 2;
                            }
                            else
                            {
                                fin = true;
                            }
                        }
                    }
                }
            }
            list->next();
            compares++;
        }
    }
};

#endif
