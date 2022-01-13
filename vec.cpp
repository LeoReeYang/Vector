#include <iostream>

using namespace std;

template <typename T>
class Vec
{
private:
    T *start;
    size_t cap, size;

public:
    Vec() : start(NULL), cap(0), size(0) {}
    Vec(T, int n) : cap(n), size(0) // T类型的vec 长度为n
    {
        start = new T[n];
    }
    int size() { return size; }
    int cap() { return cap; }

    void change_cap(int i)
    {
        cap = i;
    }

    void push_back(T a)
    {
        if (cap() - size())
        {
            start[size++] = a;
        }
        else
        {
            T *original = start;        // origin memo
            T *temp = new T[cap() * 2]; // new array

            int i;
            for (i = 0; i < cap(); i++)
                temp[i] = start[i]; // copy

            temp[i] = a;  // push
            size++;       // useage ++
            start = temp; // new address

            change_cap(cap() * 2); // change cap
            delete original[];
        }
    }
    void pop_back()
    {
        if (size)
        {
            size--;
        }
    };

    T &operator[](size_t pos)
    {
        if (pos >= 0 and pos < cap())
        {
            return data[pos];
        }
    }
};