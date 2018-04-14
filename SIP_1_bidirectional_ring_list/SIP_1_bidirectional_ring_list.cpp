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

    void showReverse()
    {
        if (head)
        {
            TElem<T> *cursor = head->prev; //перешли в конец
            do
            {
                cout << cursor->inf << "\t";
                cursor = cursor->prev;
            } while (cursor != head->prev);
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

    void deleteCurrentElement()
    {
        TElem< T > *tmp;
        if (!head)
        {
            return;
        }
        else if (current == head)
        {
            tmp = head;

            if (head->next == head)
            {
                head = NULL;
            }
            else
            {
                head = head->next;
                head->prev = tmp->prev;
                tmp->prev->next = head;
            }
        }
        else
        {
            tmp = current;
            current = current->next;
            current->prev = tmp->prev;
            tmp->prev->next = current;

        }

        delete tmp;
    }

    bool findElement(T value)
    {
        TElem<T> *cursor = head;
        do
        {
            if (cursor->inf == value)
            {
                return true;
            }
            cursor = cursor->next;
        } while (cursor != head);

        return false;
    }

    void deleteAllElements()
    {
        if (head)
        {
            head->prev->next = NULL;
            do
            {
                current = head;
                head = head->next;
                delete current;
            } while (head);
        }
        
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

        //разрываем кольцевую связь
        head->prev->next = NULL;
        head->prev = NULL;

        //сортируем как линейный односвязный список
        mergeSort(&head);

        current = head->next;
        TElem< T > *tmp = head;
        //выстраиваем обратную связь и заодно закольцовываем список
        do
        {
            if (current->next == NULL)
            {
                current->next = head;
                head->prev = current;
            }
            current->prev = tmp;
            tmp = tmp->next;
            current = current->next;
        } while (current->next != head);
        
    }

    void mergeSort(TElem< T > **root)
    {
        TElem< T > *list1, *list2;
        TElem< T > *headPtr1 = *root;

        if ((headPtr1 == NULL) || (headPtr1->next == NULL))
        {
            return;
        }

        findMid(headPtr1, &list1, &list2);

        mergeSort(&list1);
        mergeSort(&list2);

        *root = mergeList(list1, list2);

    }

    typename TElem< T >* mergeList(TElem< T > *list1, TElem< T > *list2)
    {
        TElem< T > tempheadPtr = { 0, NULL }, *tail = &tempheadPtr;

        while ((list1 != NULL) && (list2 != NULL))
        {
            TElem< T > **min = (list1->inf < list2->inf) ? &list1 : &list2;
            TElem< T > *next = (*min)->next;
            tail = tail->next = *min;
            *min = next;
        }
        tail->next = list1 ? list1 : list2;
        return tempheadPtr.next;
    }

    void findMid(TElem< T > *root, TElem< T > **list1, TElem< T > **list2)
    {
        /**
        * Возвращает указатель на элемент структуры TElem< T > рядом с серединой списка
        * и после обрезаем оригинальный список перед этим элементом
        */
        struct TElem< T > *slow, *fast;

        if ((root == NULL) || (root->next == NULL))
        {
            *list1 = root;
            *list2 = NULL;
            return;
        }
        else
        {
            /*
            два курсора, fast движется в 2 раза быстрее slow, на одну итерацию slow происходит 2 итерации fast
            за счет этого находится середина списка (когда fast == NULL, slow будет ровно в центре списка)
            */
            slow = root;
            fast = root->next;
            while (fast != NULL)
            {
                fast = fast->next;
                if (fast != NULL)
                {
                    slow = slow->next;
                    fast = fast->next;
                }
            }

            *list1 = root;
            *list2 = slow->next;
            slow->next = NULL;
        }
    }

    bool operator!()
    {
        //если у нас есть голова -> есть список, значит возвращаем true
        return (head) ? false : true;

        //(условие) ? если_да : если_нет;
        /*

        if(head != NULL)
        {
            return false;
        }

        return true;

        */

        
    }

    void operator++()
    {
        if (!head)
            return;

        if (current) // если элемент current вообще определен
        {
            current = current->next;
        }
        else
        {
            current = head; // если current не был объявлен до сих пор - присваиваем ему значение первого элемента в списке
        }

        // current = (current) ? current->next : head;
    }

    void operator --()
    {
        if (!head)
            return;

        if (current != NULL) // если элемент current вообще определен
        {
            current = current->prev;
        }
        else
        {
            current = head; // если current не был объявлен до сих пор - присваиваем ему значение первого элемента в списке
        }
        
        //current = (current) ? current->prev : head;
    }

    List< T >& operator=(List< T >& right)
    {
        if (this == &right) //проверка на самоприсваивание 
        {
            return *this;
        }

        TElem< T > *rightHead = right.getHead();
        TElem< T > *rightCurrent = rightHead;

        TElem< T > *tmp = head; // курсор в левом списке

        while (tmp || rightCurrent)
        {
            if (rightCurrent && tmp)
            {
                tmp->inf = rightCurrent->inf;
            }
            else if (tmp && !rightCurrent)
            {
                current = tmp;
                tmp = tmp->prev;
                deleteCurrentElement();
            }
            else if (!tmp && rightCurrent)
            {
                addToEnd(rightCurrent->inf);
            }

            if(tmp)
                tmp = (tmp->next == head) ? NULL : tmp->next;
            if(rightCurrent)
                rightCurrent = (rightCurrent->next == rightHead) ? NULL : rightCurrent->next;
        }
        
    }

    void sortCurrentElement() 
    {
        // проверка на пустой список
        if (!head)
        {
            return;
        }

        // проверка на наличие "текущего" элемента
        if (!current)
        {
            current = head;
        }
        else if (current == head && current->inf <= head->next->inf)
        {
            return;
        }
        else if (current == head && current->inf > head->next->inf)
        {
            head = head->next;
            head->prev = current->prev;
            head->prev->next = current->next;
        }


        // если элемент больше следующего - необходимо искать место текущему элементу во второй части списка
        // иначе до этого места
        TElem< T > *tmp = head;

        while (current->inf > tmp->inf)
        {
            tmp = tmp->next;
            if (tmp == head)
            {
                break;
            }
            
        }

        current->next = tmp->prev->next;
        current->prev = tmp->prev;
        tmp->prev->next = current;
        tmp->prev = current;
    }

    void setCurrentToHead()
    {
        if (head)
            current = head;
    }
    
    T getCopyInf()
    {
        if (!current)
        {
            current = head;
        }
        return current->inf;
    }

    T& getPointerInf()
    {
        if (!current)
        {
            current = head;
        }
        return current->inf;
    }

private:
    TElem< T >* getHead()
    {
        return head;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    
    List<int> list;
    if (!list)
    {
        cout << "asd";
    }

    for (int i = 0; i < 5; i++)
    {
        list.addToEnd(rand() % 100);
    }

    list.addToBegin(2);

    //list.show();

    list.deleteElement(0);
    
    //list.addToEnd()
    //list.show();

    list.findElement(4);
    list.findElement(11);
    //list.show();

    unsigned int start = clock();
    
    list.sort();
    unsigned int end = clock();
    cout << "ВРемени на сортировку: " << end - start << " ms\n";
    list.addSorted(9);
    list.addSorted(8);
    list.show();
    cout << endl;
    list.showReverse();

    List<int> list2;
    cout << "list2: \n";
    list2 = list;
    list.deleteCurrentElement();

    list2.show();
    cout << endl;
    list2.showReverse();
    
    cout << "------------------ \n list: \n";
    list.show();
    cout << "list2:" << endl;
    list2 = list;
    list2.show();

    cout << "------------------ \n list: \n";
    list.addToEnd(59);
    list.show();
    cout << "list2:" << endl;
    list2 = list;
    list2.show();

    cout << "------------------ \n list: \n";
    list.addToBegin(10);
    list.show();
    list.setCurrentToHead();
    list.sortCurrentElement();
    list.show();
    cout << endl;
    int a = list.getCopyInf();
    cout << "\n" << a << endl;

    system("pause");
    return 0;
}

