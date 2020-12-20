#include <iostream>

using namespace std;

template <class T>
class PointerList
{
public:
    int siz = 0;
    int cap = 1000;

    struct Node
    {
        T data;
        Node *prev;
        Node *next;
        Node &operator*();
    };

    Node head, tail;

    struct Iterator
    {
        Node *sptr;
        bool operator==(const Iterator &lhs);
        bool operator!=(const Iterator &lhs);
        bool operator<=(const Iterator &lhs);
        bool operator<(const Iterator &lhs);
        bool operator>(const Iterator &lhs);
        bool operator>=(const Iterator &lhs);

        Iterator &operator++();
        Iterator &operator++(int);

        Iterator &operator--();
        Iterator &operator--(int);

        T &operator*();
    };

    PointerList();

    // the copy constructor
    PointerList(const PointerList &source);

    // the move constructor
    PointerList(
        PointerList &&source);

    // the destructor to free memory
    ~PointerList();

    //uniwersalna referencja
    void push_front(T &&x); //wstawia element na początek
    T pop_front();          //usuwa element z początku i zwraca jego wartość lub wyjątek jeśli pusta

    void push_back(T &&x); //wstawia el na koniec
    T pop_back();          // usuwa el z końca i zwraca wartość lub wyjątek jeśli pusta

    Iterator find(const T &x); //wyszukuje el o wart x i zwraca jego poz

    Iterator erase(Iterator it); //usuwa el i zwraca iter do kolejnego ele

    Iterator insert(Iterator it, T &&x); // wstawia x przed poz it i zwraca pozycję x

    int remove(const T &x); //Usuwa wystąpienia x i zwraca ich liczbę
    int size();             // zwraca liczę el w liście
    bool empty();           //zwraca true jeśli pusta
    Iterator begin();       //zwraca iterator na pierwszy el
    Iterator end();         //zwraca iterator na koniec
    T get(Iterator);

    Iterator &operator++();
    Iterator &operator--();
    T &operator*();

    T test(Iterator it);
    T test2(Iterator it, Iterator it2);

    Iterator next(Iterator it);
    Iterator prev(Iterator it);
};

template <class T>
bool PointerList<T>::Iterator::operator==(const Iterator &lhs)
{
    return lhs.sptr == this->sptr;
}

template <class T>
bool PointerList<T>::Iterator::operator!=(const Iterator &lhs)
{
    return lhs.sptr != this->sptr;
}

template <class T>
T &PointerList<T>::Iterator::operator*()
{

    return (*sptr).data;
}

template <class T>
typename PointerList<T>::Node &PointerList<T>::Node::operator*()
{

    return *this;
}

/*
template <class T>
bool PointerList<T>::Iterator::operator<=(const Iterator &lhs)
{
    if (this->sptr >= lhs.sptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool PointerList<T>::Iterator::operator<(const Iterator &lhs)
{
    if (this->sptr < lhs.sptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool PointerList<T>::Iterator::operator>(const Iterator &lhs)
{
    if (this->sptr > lhs.sptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool PointerList<T>::Iterator::operator>=(const Iterator &lhs)
{
    if (this->sptr >= lhs.sptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

*/
template <class T>
typename PointerList<T>::Iterator &PointerList<T>::Iterator::operator++(int)
{

    Iterator::sptr = sptr->next;
    return *this;
}
template <class T>
typename PointerList<T>::Iterator &PointerList<T>::Iterator::operator--(int)
{
    Iterator::sptr = sptr->prev;
    return *this;
}

template <class T>
typename PointerList<T>::Iterator &PointerList<T>::Iterator::operator++()
{

    this->sptr = sptr->next;
    return *this;
}

template <class T>
typename PointerList<T>::Iterator &PointerList<T>::Iterator::operator--()
{
    this->sptr = sptr->prev;
    return *this;
}

template <class T>
PointerList<T>::PointerList()
{

    cap = 1000;
    siz = 0;
    head.prev = nullptr;
    head.next = &tail;
    head.data = 9999;
    tail.data = 9999;
    tail.next = nullptr;
    tail.prev = &head;
}

template <class T>
PointerList<T>::PointerList(const PointerList &source)
{
    if (!source.empty())
    {
        siz = source.siz;
        cap = source.cap;

        head = source.head;
        tail = source.tail;
    }
}

template <class T>
PointerList<T>::PointerList(PointerList &&source)
{
    siz = source.siz;
    cap = source.cap;
    *head = &source.head;
    *tail = &source.tail;
}

template <class T>
PointerList<T>::~PointerList()
{
}

template <class T>
typename PointerList<T>::Iterator PointerList<T>::begin()
{
    Iterator i;
    i.sptr = head.next;
    return i;
}

template <class T>
typename PointerList<T>::Iterator PointerList<T>::end()
{
    Iterator i;
    i.sptr = &tail;
    return i;
}

template <class T>
T PointerList<T>::test(PointerList<T>::Iterator it)
{
    Node *temp = it.sptr;

    return temp->data;
}

template <class T>
T PointerList<T>::pop_front()
{
    if (empty())
    {
        throw runtime_error("pop_front: list empty!");
    }

    Iterator i;
    i.sptr = head.next;
    head = *head.next;

    return i.sptr->data;
}

template <class T>
void PointerList<T>::push_front(T &&x)
{

    Node *i;
    i = new Node;
    Node *t;
    t = head.next;
    (*i).data = x;
    (*i).next = head.next;
    head.next = i;
    (*t).prev = i;
    (*i).prev = &head;
}

template <class T>
T PointerList<T>::pop_back()
{

    if (empty())
    {
        throw runtime_error("pop_back: list empty!");
    }

    Iterator i;
    i.sptr = tail.prev;
    T temp = i.sptr->data;
    Iterator j = i--;
    j.sptr->next = &tail;
    tail.prev = i.sptr;

    return temp;
}

template <class T>
void PointerList<T>::push_back(T &&x)
{

    Node *i;
    i = new Node;
    Node *t;
    t = tail.prev;
    (*i).data = x;
    (*i).prev = tail.prev;
    tail.prev = i;
    (*t).next = i;
    (*i).next = &tail;
}

template <class T>
bool PointerList<T>::empty()
{
    if (tail.prev == &head && head.next == &tail)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
int PointerList<T>::size()
{
    Iterator i = begin();
    int w = 0;
    while (i != end())
    {
        i++;
        ++w;
    }
    return w;
}

template <class T>
typename PointerList<T>::Iterator PointerList<T>::erase(Iterator it)
{
    Iterator l = it--;
    it++;
    Iterator r = it++;
    l.sptr->next = r.sptr;
    r.sptr->prev = l.sptr;
    return r;
}

template <class T>
typename PointerList<T>::Iterator PointerList<T>::find(const T &x)
{
    Iterator i = begin();
    for (int j = 0; j <= size(); j++)
    {
        if (test(i) == x)
        {
            return i;
        }
        i++;
    }
    return end();
}

template <class T>
typename PointerList<T>::Iterator PointerList<T>::insert(Iterator it, T &&x)
{
    Iterator l = it--;

    it++;
    Iterator r = it++;
    Node *i;
    i = new Node;
    Iterator *in;
    in = new Iterator;
    in->sptr = i;
    i->data = x;
    i->prev = l.sptr;
    i->next = r.sptr;
    l.sptr->next = i;
    r.sptr->prev = i;
    return *in;
}

template <class T>
int PointerList<T>::remove(const T &x)
{

    Iterator i = begin();
    int w = 0;
    for (int j = 0; j <= size(); j++)
    {
        if (test(i) == x)
        {
            erase(i);
            w++;
        }
        i++;
    }
    return w;
}