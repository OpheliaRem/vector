#pragma once
#include <string>

template<class T>
class Vector {

    const int capacity_measure = 100;
    size_t capacity;
    size_t size;
    T* array;

public:

    Vector() : size(0) {
        capacity = capacity_measure;
        array = new T[capacity];
    }

    ~Vector() {
        size = 0;
        capacity = 0;
        delete[] array;
    }

    //copy constructor
    Vector(const Vector& other)
    : capacity_measure(other.capacity_measure),
    capacity(other.capacity),
    size(other.size) {
        array = new T[capacity];
        for (int i = 0; i < size; ++i) {
            array[i] = other.array[i];
        }
    }

    //move constructor
    Vector(Vector&& other) noexcept
    : capacity_measure(other.capacity_measure),
    capacity(other.capacity),
    size(other.size),
    array(other.array) {
        other.array = nullptr;
    }

    //copy/move assignment operator
    Vector& operator=(Vector other) {
        std::swap(array, other.array);
        capacity_measure = other.capacity_measure;
        capacity = other.capacity;
        size = other.size;
        return *this;
    }

    size_t get_size() const {
        return size;
    }

    void push_back(const T& element) {
        ++size;

        if (size < capacity) {
            array[size - 1] = element;
            return;
        }

        capacity += capacity_measure;
        T* new_array = new T[capacity];
        for (int i = 0; i < size; ++i) {
            new_array[i] = array[i];
        }

        delete[] array;
        array = new_array;

        array[size - 1] = element;
    }

    void pop_back() {
        if (is_empty()) {
            throw std::exception();
        }

        --size;
    }

    bool is_empty() const {
        return size <= 0;
    }

    const T& front() const {
        if (is_empty()) {
            throw std::exception();
        }

        return array[0];
    }

    const T& back() const {
        if (is_empty()) {
            throw std::exception();
        }

        return array[size - 1];
    }

    //immutable(const) access to an element by index
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::exception();
        }

        return array[index];
    }

    void insert(size_t index, const T& data) {
        if (index > size) {
            throw std::exception();
        }

        if (index == size) {
            return push_back(data);
        }

        array[index] = data;
    }

    void clear() {
        size = 0;
    }
};