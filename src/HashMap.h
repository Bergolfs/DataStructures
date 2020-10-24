#pragma once

namespace HashMap {

template <class T>
struct HashFunc {
    size_t operator()(T* val, size_t capacity) const
    {
        return *reinterpret_cast<size_t*>(val) % capacity;
    }
};

template <class K, class V>
struct entry {

    entry(const K& key, const V& value, entry* next = nullptr)
        : key_(key)
        , value_(value)
        , next_(next) {};

    ~entry() {};

    entry(const entry<K, V>& other)
    {
        key_ = other.key_;
        value_ = other.value_;
        next_ = nullptr;
    }

    const entry<K, V>& operator=(entry<K, V> other)
    {
        swap(other);
        return *this;
    }

    entry(const entry<K, V>&& other)
    {
        key_ = other.key_;
        value_ = other.value_;
        next_ = nullptr;
    }

    const K& getKey() const
    {
        return key_;
    }

    const V& getValue() const
    {
        return value_;
    }

    void setValue(const V& val)
    {
        value_ = val;
    }

    entry<K, V>* getNext() const
    {
        return next_;
    }

    void setNext(entry<K, V>* item)
    {
        next_ = item;
    }

private:
    K key_;
    V value_;
    entry<K, V>* next_;
    void swap(const entry<K, V>& other)
    {
        std::swap(key_, other.key_);
        std::swap(value_, other.value_);
        std::swap(next_, other.next_);
    };
};

template <class K, class V, class F = HashFunc<K>>
struct HashMap {

private:
    entry<K, V>** table_;
    size_t capacity_;
    size_t size_;
    F hashFunc;

    size_t getHash(const K* val)
    {
        return hashFunc(const_cast<K*>(val), capacity_);
    }

public:
    explicit HashMap(size_t capacity = 256)
        : table_(nullptr)
        , capacity_(capacity)
        , size_(0)
        , hashFunc()
    {
        table_ = new entry<K, V>*[capacity_];
        for (size_t i = 0; i < capacity_; ++i) {
            table_[i] = nullptr;
        }
    };

    ~HashMap()
    {
        for (size_t i = 0; i < capacity_; ++i) {
            delete table_[i];
        }

        delete[] table_;
    };

    void insert(const K& key, const V& val)
    {

        size_t hashVal = getHash(&key);
        entry<K, V>* prev = nullptr;
        auto target = table_[hashVal];

        // Find the chain tail or current element
        while (target != nullptr && target->getKey() != key) {
            prev = target;
            target = target->getNext();
        }

        if (target == nullptr) {
            target = new entry<K, V>(key, val);
            if (prev == nullptr) {
                // Insert as a first entry in chain
                table_[hashVal] = target;
            } else {
                // Append to end of existing chain
                prev->setNext(target);
            }
            ++size_;
        } else {
            // Update value
            target->setValue(val);
        }
    }

    entry<K, V> get(const K& key)
    {
        size_t hashVal = getHash(&key);
        auto target = table_[hashVal];

        // Find current element in chain
        while (target != nullptr && target->getKey() != key) {
            target = target->getNext();
        }

        if (target == nullptr) {
            throw std::invalid_argument("Invalid key!");
        }
        return *target;
    }

    bool remove(const K& key)
    {
        size_t hashVal = getHash(&key);
        entry<K, V>* prev = nullptr;
        auto target = table_[hashVal];

        // Find current element in chain
        while (target != nullptr && target->getKey() != key) {
            prev = target;
            target = target->getNext();
        }

        if (target == nullptr) {
            return false;
        } else {
            prev->setNext(target->getNext());
            delete target;
            --size_;
            return true;
        }
    }

    void print()
    {
        using std::cout;
        using std::endl;

        cout << "Size: " << size_ << endl
             << "Capacity: " << capacity_ << endl;
        cout << "Table: " << endl;

        for (size_t i = 0; i < capacity_; ++i) {
            auto target = table_[i];
            if (target != nullptr) {
                cout << "Table[" << i << "]: ";
                while (target != nullptr) {
                    cout << "<" << target->getKey() << ", " << target->getValue() << ">"
                         << " -> ";
                    target = target->getNext();
                }
                cout << "null" << endl;
            }
        }
    }
};
}
