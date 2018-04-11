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
    
    bool isEmpty()
    {
        return (head) ? true : false;
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

        //разрываем кольцевую св€зь
        head->prev->next = NULL;
        head->prev = NULL;

        //сортируем как линейный односв€зный список
        mergeSort(&head);

        current = head->next;
        TElem< T > *tmp = head;
        //выстраиваем обратную св€зь и заодно закольцовываем список
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
        * ¬озвращает указатель на элемент структуры TElem< T > р€дом с серединой списка
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
            два курсора, fast движетс€ в 2 раза быстрее slow, на одну итерацию slow происходит 2 итерации fast
            за счет этого находитс€ середина списка (когда fast == NULL, slow будет ровно в центре списка)
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
        return (head) ? true : false;
        //если выгл€дит слишком стремно, можешь использовать следующий аналог
        /*

        if(head != NULL)
        {
            return true;
        }

        return false;

        */
    }

    void operator ++()
    {
        if (current) // если элемент current вообще определен
        {
            current = current->next;
        }
        else
        {
            current = head; // если current не был объ€влен до сих пор - присваиваем ему значение первого элемента в списке
        }
    }

    void operator --()
    {
        if (current) // если элемент current вообще определен
        {
            current = current->prev;
        }
        else
        {
            current = head; // если current не был объ€влен до сих пор - присваиваем ему значение первого элемента в списке
        }
    }

    List< T >& operator=(List< T >& right)
    {
        // вызыватьс€ будет как
        // list1 = list2; (list1 - левый, list2 - правый)
        // следовательно эта функци€ будет вызвана внутри экземпл€ра класса list1 

        if (right.isEmpty())
        {
            TElem< T > *rightHead = right.getHead();
            TElem< T > *rightCurr = rightHead;
            // TODO: присваивание текущему списку правого

            if (this == &right) //проверка на самоприсваивание 
            {
                return *this;
            }

            if (this) //если список в который записываем не был пустым
            {
                deleteAllElements();
            }

            //создали голову дл€ текущего списка 
            TElem< T > *leftHead = new TElem< T >;
            leftHead->inf = rightHead->inf;
            leftHead->next = NULL;
            leftHead->prev = NULL;

            //прописали в внутриклассовые переменные 
            head = leftHead;
            current = head;

            //переходим к следующему элементу в правом списке
            if (rightCurr->next)
            {
                rightCurr = rightCurr->next;
            }

            TElem< T >* prevCurr = NULL;

            //проходим по всему остальному списку копиру€ поэлементно 
            do
            {
                // выдел€ем пам€ть под новый элемент и заполн€ем
                TElem< T > * leftTmp = new TElem< T >;
                leftTmp->inf = rightCurr->inf;
                leftTmp->next = NULL;
                leftTmp->prev = NULL;

                current->next = leftTmp; //помещаем скопированный элеемнт в левый список
                prevCurr = current;
                current = current->next;
                current->prev = prevCurr; // делаем обратную св€зь
                rightCurr = rightCurr->next;
            } while (rightCurr != rightHead);

            current->next = head;
            head->prev = current;

        }
    }

    TElem< T >* getHead()
    {
        return head;
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
    cout << "¬–емени на сортировку: " << end - start << " ms\n";
    list.addSorted(9);
    list.addSorted(8);
    list.show();
    cout << endl;
    list.showReverse();

    

    

    List<int> list2;
    list2 = list;
    list2.show();
    cout << endl;
    list2.showReverse();

    system("pause");
    return 0;
}

