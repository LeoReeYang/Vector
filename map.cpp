#include <iostream>
#include <list>
using namespace std;
template <typename T>
class Vec
{
private:
    T *_start;
    size_t _cap, _size;

private:
    void expand_push(const T &a)
    {
        T *t = new T[cap() << 1];
        change_cap(cap() << 1); // change the capacity

        for (int i = 0; i < size(); i++)
        {
            t[i] = move(_start[i]);
        }

        delete[] _start;     // delete original memory
        _start = t;          // point to new memory
        _start[_size++] = a; // pushback new element
    }

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
            _start[_size++] = a;
        else
            expand_push(a);
    }
    void pop_back()
    {
        if (_size)
            _size--;
        else
            throw "Vector is empty!";
    }

    T &operator[](size_t pos)
    {
        if (pos >= 0 and pos < size())
            return _start[pos];
        else
            throw "out of bound!";
    }
};

template <typename K, typename V>

class Node
{
public:
    K _key;
    V _value;
    Node *next;

    Node() {}
    Node(K key, V value) : _key(key), _value(value), next(nullptr) {}
    ~Node() {}

    Node &operator=(const Node &node)
    {
        _key = node._key;
        _value = node._value;
        next = node.next;
        return *this;
    }
};

template <typename K, typename V>
class Map
{
private:
    size_t _size;
    V nullvalue;
    Node<K, V> **table;

public:
    Map(int size) : _size(size)
    {
        table = new Node<K, V> *[_size];
        for (int i = 0; i < _size; i++)
            table[i] = nullptr;
    }
    size_t getSize() { return _size; }
    void incresSize() { _size++; }
    void decresSize() { _size--; }
    V &operator[](const K &key);
    V &find(const K &key);
    bool del(const K &key);
    bool insert(const K &key, const V &value);
};

template <typename K, typename V>
bool Map<K, V>::insert(const K &key, const V &value)
{
    size_t index = std::hash<K>{}(key) % getSize();
    Node<K, V> *node = new Node<K, V>(key, value);

    node->next = table[index];
    table[index] = node;
    return true;
}

template <typename K, typename V>
V &Map<K, V>::operator[](const K &key)
{
    return find(key);
}
template <typename K, typename V>
V &Map<K, V>::find(const K &key)
{
    size_t index = std::hash<K>{}(key) % getSize();

    if (table[index] == nullptr)
    {
        return nullvalue;
        throw "not exsit.";
    }
    else
    {
        Node<K, V> *node = table[index];
        while (node)
        {
            if (node->_key = key)
                return node->_value;
            else
                node = node->next;
        }
        return nullvalue;
    }
}
template <typename K, typename V>
bool Map<K, V>::del(const K &key)
{
    size_t index = std::hash<K>{}(key) % getSize();
    Node<K, V> *node = table[index];
    Node<K, V> *pre = nullptr;

    while (node)
    {
        if (node->_key == key)
        {
            if (pre == nullptr)
                table[index] = node->next;
            else
                pre->next = node->next;

            delete node;
            return true;
        }
        pre = node;
        node = node->next;
    }
    return false;
}

int main()
{
    Map<int, int> m(10);
    m.insert(1, 3);

    if (m.find(1) == 3)
        cout << "yes!" << endl;
    if (m.del(1))
        cout << "yes!" << endl;
    return 0;
}