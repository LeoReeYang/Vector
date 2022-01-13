#include <iostream>

using namespace std;

template <typename T>
class Vec
{
private:
    T *start;
    T *now;
    T *end;
    size_t cap, size;

public:
    Vec() : start(NULL), now(NULL), end(NULL), cap(0), size(0) {}
    Vec(T, int n) : cap(n), size(n) // T类型的vec 长度为n
    {
        start = new T[n];
        now = start;
        end = start + sizeof(T) * (n - 1);
    }
    int size() { return size; }
    int cap() { return cap; }

    void change_size(int i)
    {
        size = i;
    }
    void change_cap(int i)
    {
        cap = i;
    }

    void push_back(T a)
    {
        if (size())
        {
            *now = a;
            now++;
        }
        else
        {
            T *temp = new T[cap() * 2]; // new array
            int i;
            for (i = 0; i < cap(); i++)
                temp[i] = start[i]; // copy
            temp[i] = a;            // push
            start = temp;
            now = temp + sizeof(T) * i - 1;
            end = start + sizeof(T) * cap() * 2 - 1;
            change_cap(cap() * 2);
            change_size(int(now - start));

            delete temp[];
        }
    }
    void pop_back()
    {
        if (now - start >= 0 and now < end)
        {
            delete now;
            now--;
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