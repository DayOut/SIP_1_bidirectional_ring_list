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
            cout << "������� " << value <<" ���� � ������. \n";
        }
        else
        {
            cout << "������� " << value << " ����������� � ������. \n";
        }
    }

private:

};

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    List<int> list;

    for (int i = 0; i < 7; i++)
    {
        list.addToEnd(i);
    }

    
    list.addToBegin(2);

    list.show();

    list.addSorted(9);
    list.addSorted(8);

    list.deleteElement(0);
    
    //list.addToEnd()
    list.show();

    list.findElement(4);
    list.findElement(11);


    return 0;
}

