#pragma once
#include <iostream>
#include <stdexcept>

template<typename K, typename V>
struct HashNode {
    K key;
    V value;
    HashNode* next;
    HashNode(K k, V v) : key(k), value(v), next(nullptr) {}
};

template<typename K, typename V>
class HashMap {
private:
    HashNode<K, V>** table;
    int capacity;
    int size;

    int hashFunction(K key);

public:
    HashMap(int cap = 100);
    ~HashMap();

    void insert(K key, V value);
    V get(K key);
    bool remove(K key);
    int getSize() const;
    bool isEmpty() const;
    int getCapacity() const { return capacity; }
    HashNode<K, V>** getTable() const { return table; }
};

#include "HashMap.tpp"
