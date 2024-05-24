// HashMap.tpp

template<typename K, typename V>
HashMap<K, V>::HashMap(int cap) : capacity(cap), size(0) {
    table = new HashNode<K, V>*[capacity]();
};

template<typename K, typename V>
HashMap<K, V>::~HashMap() {
    for (int i = 0; i < capacity; ++i) {
        HashNode<K, V>* entry = table[i];
        while (entry != nullptr) {
            HashNode<K, V>* prev = entry;
            entry = entry->next;
            delete prev;
        }
    }
    delete[] table;
}

template<typename K, typename V>
int HashMap<K, V>::hashFunction(K key) {
    return std::hash<K>()(key) % capacity;
}

template<typename K, typename V>
void HashMap<K, V>::insert(K key, V value) {
    int hashIndex = hashFunction(key);
    HashNode<K, V>* prev = nullptr;
    HashNode<K, V>* entry = table[hashIndex];

    while (entry != nullptr && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr) {
        entry = new HashNode<K, V>(key, value);
        if (prev == nullptr) {
            table[hashIndex] = entry;
        } else {
            prev->next = entry;
        }
        size++;
    } else {
        entry->value = value;
    }
}

template<typename K, typename V>
V HashMap<K, V>::get(K key) {
    int hashIndex = hashFunction(key);
    HashNode<K, V>* entry = table[hashIndex];

    while (entry != nullptr) {
        if (entry->key == key) {
            return entry->value;
        }
        entry = entry->next;
    }
    throw std::runtime_error("Key not found");
}

template<typename K, typename V>
bool HashMap<K, V>::remove(K key) {
    int hashIndex = hashFunction(key);
    HashNode<K, V>* prev = nullptr;
    HashNode<K, V>* entry = table[hashIndex];

    while (entry != nullptr && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr) {
        return false;
    } else {
        if (prev == nullptr) {
            table[hashIndex] = entry->next;
        } else {
            prev->next = entry->next;
        }
        delete entry;
        size--;
        return true;
    }
}

template<typename K, typename V>
int HashMap<K, V>::getSize() const {
    return size;
}

template<typename K, typename V>
bool HashMap<K, V>::isEmpty() const {
    return size == 0;
}
