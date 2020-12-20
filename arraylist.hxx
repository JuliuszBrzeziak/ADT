

using namespace std;

template <class T>
class ArrayList
{
public:
    int siz;
    T *ptr;
    int cap;

    struct Iterator
    {
        T *sptr;
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

    ArrayList();

    // the copy constructor
    ArrayList(const ArrayList &source);

    // the move constructor
    ArrayList(ArrayList &&source);

    // the destructor to free memory
    ~ArrayList();

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
    // bool operator==(const ArrayList &lhs);
    // bool operator!=(const ArrayList &lhs);
    // bool operator<=(const ArrayList &lhs);
    // bool operator<(const ArrayList &lhs);
    // bool operator>(const ArrayList &lhs);
    // bool operator>=(const ArrayList &lhs);

    Iterator &operator++();
    Iterator &operator--();
    T &operator*();

    T test(Iterator it);
    T test2(Iterator it, Iterator it2);

    Iterator next(Iterator it);
    Iterator prev(Iterator it);
};

template <class T>
ArrayList<T>::ArrayList()
{

    ptr = new T[1000]{};
    cap = 1000;
    siz = 0;
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList &source)
{
    if (!source.isEmpty())
    {
        siz = source.siz;
        cap = source.cap;

        ptr = new T[siz];
        for (int i = 0; i < siz; i += 1)
        {
            ptr[i] = source.ptr[i];
        }
    }
}

template <class T>
ArrayList<T>::ArrayList(ArrayList &&source)
{
    siz = source.siz;
    cap = source.cap;
    ptr = source.ptr;

    source.ptr = nullptr;
    source.siz = 0;
}

template <class T>
ArrayList<T>::~ArrayList()
{
    delete[] ptr;
}

template <class T>
bool ArrayList<T>::empty()
{
    if (siz == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
void ArrayList<T>::push_back(T &&x)
{
    if (siz == cap)
    {
        throw runtime_error("siz==cap");
    }

    *end() = x;
    siz++;
}

template <class T>
T ArrayList<T>::pop_back()
{
    if (empty())
    {
        throw runtime_error("popbacklist is empty!");
    }
    T temp = *end()--;

    siz--;

    return temp;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::begin()
{

    Iterator a;
    a.sptr = ptr;

    return a;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::end()
{
    Iterator a;
    a.sptr = ptr + siz;
    return a;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::insert(Iterator it, T &&x)
{

    for (Iterator iii = end(); iii >= it; iii = prev(iii))
    {
        *(iii.sptr + 1) = *iii.sptr;
    }
    *it.sptr = x;
    siz++;
    return it;
}

template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::operator++()
{
    Iterator::sptr++;
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator++()
{
    Iterator::sptr++;
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::operator--()
{
    Iterator::sptr--;
    return *this;
}

template <class T>
T ArrayList<T>::test(ArrayList<T>::Iterator it)
{
    return *it.sptr;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::next(Iterator it)
{
    Iterator temp = it;
    temp.sptr++;
    return temp;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::prev(Iterator it)
{
    Iterator temp = it;
    temp.sptr--;
    return temp;
}

template <class T>
bool ArrayList<T>::Iterator::operator==(const Iterator &lhs)
{
    return lhs.sptr == this->sptr;
}

template <class T>
bool ArrayList<T>::Iterator::operator!=(const Iterator &lhs)
{
    return lhs.sptr != this->sptr;
}

template <class T>
T &ArrayList<T>::Iterator::operator*()
{

    return *sptr;
}
template <class T>
bool ArrayList<T>::Iterator::operator<=(const Iterator &lhs)
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
bool ArrayList<T>::Iterator::operator<(const Iterator &lhs)
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
bool ArrayList<T>::Iterator::operator>(const Iterator &lhs)
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
bool ArrayList<T>::Iterator::operator>=(const Iterator &lhs)
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
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator++(int)
{
    Iterator::sptr++;
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator--(int)
{
    Iterator::sptr--;
    return *this;
}

template <class T>
void ArrayList<T>::push_front(T &&x)
{

    for (Iterator iii = end(); iii >= begin(); iii = prev(iii))
    {
        *(iii.sptr + 1) = *iii.sptr;
    }
    *begin() = x;
    siz++;
}

template <class T>
T ArrayList<T>::pop_front()

{

    if (empty())
    {
        throw runtime_error("POPfront:list is empty!");
    }

    T temp = *begin();
    Iterator a = begin();

    for (a; a < end(); ++a)
    {
        *a = *next(a);
    }

    siz--;
    return temp;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::erase(Iterator it)
{

    Iterator temp = it;

    for (Iterator a = it; a < end(); a = next(a))
    {

        *a.sptr = *(next(a));
    }

    siz--;
    return temp;
}

template <typename T>
int ArrayList<T>::size()
{
    return siz;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::find(const T &x)
{
    for (Iterator i = begin(); i < end(); i++)
    {
        if (*i == x)
        {
            return i;
        }
    }
    return end();
}
template <class T>
int ArrayList<T>::remove(const T &x)
{
    int w = 0;
    Iterator i = begin();

    for (Iterator i = begin(); i < end(); i = find(x))
    {
        w++;
        erase(i);
    }
    return --w;
}