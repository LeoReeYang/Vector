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
    Vec(size_t n) : _cap(n), _size(0)
    {
        _start = new T[n];
    }

    Vec(const Vec &t) : _cap(t._cap), _size(t._size)
    {
        _start = new T[cap()];
        for (int i = 0; i < t._size(); i++)
            _start[i] = t._start[i];
    }

    Vec(Vec &&rhs) // move build func
    {
        this->_start = rhs._start;
        this->_size = rhs._size;
        this->_cap = rhs._cap;
        rhs._start = nullptr;
        rhs.size = 0;
        rhs._cap = 0;
    }

    ~Vec()
    {
        delete[] _start;
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
            T *t = new T[cap() << 1];
            change_cap(cap() << 1); // change the capacity

            int i;
            for (i = 0; i < size(); i++)
            {
                t[i] = move(_start[i]);
            }

            delete[] _start; // delete original memory
            _start = t;      // point to new memory
            _start[i] = a;   // pushback new element
            _size++;
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
            return _start[pos];
        else
            throw "out of bound!";
    }
};

int main() // test
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

    Vec<int> t1(10);
    Vec<int> t2 = move(t1);
}