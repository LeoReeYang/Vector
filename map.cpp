#include <iostream>
#include <list>
using namespace std;
template <typename K, typename V>
class Map
{
private:
    size_t _size;
    V nullvalue;

private:
    template <typename Key, typename Value>
    class Node
    {
    public:
        Key _key;
        Value _value;
        Node *next;

        Node() {}
        Node(Key key, Value value) : _key(key), _value(value), next(nullptr) {}
        ~Node() {}

        Node &operator=(const Node &node)
        {
            _key = node._key;
            _value = node._value;
            next = node.next;
            return *this;
        }
    };

private:
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