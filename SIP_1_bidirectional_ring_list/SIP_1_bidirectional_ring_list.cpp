// SIP_1_bidirectional_ring_list.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

template <typename T>
class List
{
private:
    template<typename T>
    struct TElem
    {
        T             inf;
		TElem< T >    *next;
        TElem< T >    *prev;
    };

    TElem<T> *head, *current;

public:
    List()
    {
        head = current = NULL;
    }

    ~List()
    {
        deleteAllElements();
    }

    void show()
    {
        if (head)
        {
            TElem<T> *cursor = head;
            do
            {
                cout << cursor->inf << "\t";
                cursor = cursor->next;
            } while (cursor != head);
            cout << endl;
        }
    }

    void addToEnd(T value)
    {
        TElem< T > *tmp = new TElem < T >;
        tmp->inf = value;

        if (head)
        {
            tmp->next = head;
            tmp->prev = head->prev;
            head->prev->next = tmp;
            head->prev = tmp;
        }
        else
        {
            head = tmp->next = tmp->prev = tmp;
        }
    }

    void addToBegin(T value)
    {
        TElem< T > *tmp = new TElem< T >; 
        tmp->inf = value;

        if (head)
        {
            tmp->next = head;
            tmp->prev = head->prev;
            head->prev->next = tmp;
            head->prev = tmp;
        }
        else
        {
            head = tmp->next = tmp->prev = tmp;
        }

        head = tmp;
    }

    void addSorted(T value)
    {
        if (head)
        {
            TElem< T > *tmp = new TElem< T >;
            tmp->inf = value;

            TElem< T > *cursor = head;
            do
            {
                if (cursor->inf >= value)
                {
                    break;
                }
                cursor = cursor->next;
            } while (cursor != head);

            tmp->next = cursor;
            tmp->prev = cursor->prev;
            cursor->prev->next = tmp;
            cursor->prev = tmp;
        }
        else
        {
            addToBegin(value);
        }
    }

    void deleteElement(T value)
    {
        if (head)
        {
            TElem< T > *cursor = head;
            do
            {
                if (cursor->inf == value)
                {
                    cursor->prev->next = cursor->next;
                    cursor->next = cursor->prev;
                    delete cursor;
                    break;
                }
                cursor = cursor->next;
            } while (cursor != head);
        }
    }

    void findElement(T value)
    {
        bool findFlag = false;

        TElem<T> *cursor = head;
        do
        {
            if (cursor->inf == value)
            {
                findFlag = true;
                break;
            }
            cursor = cursor->next;
        } while (cursor != head);

        if (findFlag == true)
        {
            cout << "Ёлемент " << value <<" есть в списке. \n";
        }
        else
        {
            cout << "Ёлемент " << value << " отсутствует в списке. \n";
        }
    }

    void deleteAllElements()
    {
        head->prev->next = NULL;
        do
        {
            current = head;
            head = head->next;
            delete current;           
        } while (head);
    }

    void sort()
    {

        /*
            it may helps: 
                https://ide.geeksforgeeks.org/GWuAsj
                https://ideone.com/EdBruH
                https://github.com/ashishnith09/DSAlgosinC/blob/master/LinkedList/MergeSort%20On%20DLL%20by%20passing%20variable%20by%20refrences
                https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/
                https://stackoverflow.com/questions/26684481/linked-list-merge-sort

                MergeSort on Doubly Linked List
                http://www.cplusplus.com/forum/beginner/199976/
                https://stackoverflow.com/questions/47170967/merge-sort-on-a-doubly-linked-list-c
                https://www.google.com.ua/search?ei=XRzJWt2kArOTmwXU9KbIDw&q=mergesort+double+list+c%2B%2B&oq=mergesort+double+list+c%2B%2B&gs_l=psy-ab.3...4216612.4217431.0.4227108.6.6.0.0.0.0.158.397.0j3.3.0....0...1c.1.64.psy-ab..3.0.0....0.Jws_DfvwYAA

        */


        head->prev->next = NULL;
        head->prev = NULL;

        mergeSort(head);
        cout << "sort finished\n";

        current = head;
        do
        {
            if (current->next == NULL)
            {
                current->next = head;
                head->prev = current;
            }
            current = current->next;
        } while (current->next != head);

    }
  
    // Function to merge two linked lists
    TElem< T >* merge(TElem< T >* first, TElem< T >* second)
    {
        // If first linked list is empty
        if (!first)
            return second;

        // If second linked list is empty
        if (!second)
            return first;

        // Pick the smaller value
        if (first->inf < second->inf)
        {
            first->next = merge(first->next, second);
            first->next->prev = first;
            first->prev = NULL;
            return first;
        }
        else
        {
            second->next = merge(first, second->next);
            second->next->prev = second;
            second->prev = NULL;
            return second;
        }
    }

    // Function to do merge sort
    TElem< T >* mergeSort(TElem< T >*head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        TElem< T >* second = split(head);

        // Recur for left and right halves
        head = mergeSort(head);
        second = mergeSort(second);

        // Merge the two sorted halves
        return merge(head, second);
    }

    TElem< T >* split(TElem< T >* head)
    {
        TElem< T >* fast = head, *slow = head;
        while (fast->next && fast->next->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        TElem< T >* temp = slow->next;
        slow->next = NULL;
        return temp;
    }


private:

};

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    List<int> list;

    for (int i = 0; i < 1000000; i++)
    {
        list.addToEnd(rand() % 100);
    }

    
    list.addToBegin(2);

    //list.show();

    /*
    list.addSorted(9);
    list.addSorted(8);*/

    list.deleteElement(0);
    
    //list.addToEnd()
    //list.show();

    list.findElement(4);
    list.findElement(11);

    unsigned int start = clock();
    
    list.sort();
    unsigned int end = clock();
    cout << "¬–емени на сортировку: " << end - start << " ms\n";
    //list.show();




    return 0;
}

