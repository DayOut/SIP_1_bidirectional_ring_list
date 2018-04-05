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
        T		      inf;
		TElem< T >    *next;
        TElem< T >    *prev;
    };

    TElem<T> *head, *current, *tail;

public:
    List()
    {
        head = current = tail = NULL;
    }

    ~List()
    {

    }

    void show()
    {
        TElem<T> *cursor = head;
        do
        {
            cout << cursor->inf << "\t";
            cursor = cursor->next;
        } while (cursor != head);
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

    }

private:

};

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    List<int> list;

    for (int i = 0; i < 10; i++)
    {
        list.addToEnd(i);
    }

    list.addToBegin(11);
    list.addToBegin(12);
    list.addToBegin(13);

    //list.addToEnd()
    list.show();

    return 0;
}

