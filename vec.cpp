#include <iostream>

using namespace std;

template <typename T>
class Vec
{
private:
    T *_start;
    size_t _cap, _size;

public:
    Vec() : _start(nullptr), _cap(0), _size(0) {}
    Vec(size_t n) : _cap(n), _size(0) // T类型的vec 长度为n
    {
        _start = new T[n];
    }
    int size() { return _size; }
    int cap() { return _cap; }

    void change_cap(int i)
    {
        _cap = i;
    }

    void push_back(const T &a)
    {
        if (cap() - size())
        {
            _start[_size++] = a;
        }
        else
        {
            T *original = _start;        // origin memo
            T *temp = new T[cap() << 1]; // new array

            int i;
            for (i = 0; i < cap(); i++)
                temp[i] = _start[i]; // copy

            temp[i] = a;   // push
            _size++;       // useage ++
            _start = temp; // new address

            change_cap(cap() * 2); // change _cap
            delete[] original;
        }
    }
    void pop_back()
    {
        if (_size)
        {
            _size--;
        }
    }

    T &operator[](size_t pos)
    {
        if (pos >= 0 and pos < size())
        {
            return _start[pos];
        }
        else
        {
            throw "out of bound!";
        }
    }
};

int main()
{
    Vec<int> t(5);
    for (int i = 0; i < 5; i++)
    {
        t.push_back(i + 1);
        cout << t[i] << endl;
    }

    t.pop_back();
    t.pop_back();

    for (int i = 0; i < t.size(); i++)
    {
        cout << t[i] << endl;
    }
}