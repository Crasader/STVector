//
// Created by Saul Moreno Abril on 18/06/2018.
//

#ifndef STVECTOR_STVECTOR_H
#define STVECTOR_STVECTOR_H

#include <vector>
#include <thread>

template <class T>
class STVector {
private:
protected:
    std::mutex _mutex;
    std::vector<T> _vector;


public:
    STVector() = default;

    // Add element to the end
    void push_back(const T& v);    //Añadir un elemento al final del vector
    void push_back(T&& v);

    // Clear
    void clear();

    // Resize
    void resize(size_t n);
    // Reserve
    void reserve(size_t n);

    // Alloc and insert
    T& emplace_back(T&& v);

    // Remove element in a range
    void erase(std::size_t first, std::size_t lenght);

    // Delete last element
    T pop_back();

    // Size
    size_t size();

    // Capacity
    size_t capacity();

    // Is empty
    bool empty();

    // Operator [] to get an element
    T& operator[](size_t idx);
    //const T& operator[](size_t idx);

    // Get last element
    T& back();
    //const T& back() const;

    ///////////////////////
    // Helper
    //////////////////////

    // Call a function for element
    void foreach(std::function<void(const T&)> f) const;   //Recorre el vector y ejecuta la función pasada por parámetro para cada elemento
    void foreach(std::function<void(T&)> f);

    // Swap
    void swapElement(size_t pos, T *other);
    void swap(STVector &other);
};


template <class T>
void STVector<T>::push_back (const T& v) {
    std::lock_guard<std::mutex> guard(_mutex);
    _vector.push_back(v);
}

template <class T>
void STVector<T>::push_back (T&& v) {
    std::lock_guard<std::mutex> guard(_mutex);
    return _vector.push_back(v);
}

template <class T>
void STVector<T>::clear () {
    std::lock_guard<std::mutex> guard(_mutex);
    _vector.clear();
}

template <class T>
void STVector<T>::resize (size_t n) {
    std::lock_guard<std::mutex> guard(_mutex);
    _vector.reserve(n);
}

template <class T>
void STVector<T>::reserve (size_t n) {
    std::lock_guard<std::mutex> guard(_mutex);
    _vector.reserve(n);
}

template <class T>
T& STVector<T>::emplace_back(T&& v) {
    std::lock_guard<std::mutex> guard(_mutex);
    return _vector.emplace_back(v);
}

template <class T>
void STVector<T>::erase(std::size_t first, std::size_t lenght) {
    std::lock_guard<std::mutex> guard(_mutex);
    _vector.erase(_vector.begin() + first, _vector.begin() + lenght);
}

template <class T>
T STVector<T>::pop_back() {
    std::lock_guard<std::mutex> guard(_mutex);
    return _vector.pop_back();
}

template <class T>
size_t STVector<T>::size() {
    std::lock_guard<std::mutex> guard(_mutex);
    return _vector.size();
}

template <class T>
size_t STVector<T>::capacity() {
    std::lock_guard<std::mutex> guard(_mutex);
    return _vector.capacity();
}

template <class T>
bool STVector<T>::empty() {
    std::lock_guard<std::mutex> guard(_mutex);
    return _vector.empty();
}

template <class T>
T& STVector<T>::operator[](size_t idx) {
    std::lock_guard<std::mutex> guard(_mutex);
    return _vector[idx];
}

template <class T>
T& STVector<T>::back() {
    std::lock_guard<std::mutex> guard(_mutex);
    return _vector.back();
}


template <class T>
void STVector<T>::foreach(std::function<void(const T &)> f) const {
    std::lock_guard<std::mutex> guard(_mutex);
    for (auto &element : _vector) {
        f(element);
    }
}

template <class T>
void STVector<T>::foreach(std::function<void(T & )> f) {
    std::lock_guard<std::mutex> guard(_mutex);
    for (auto &element : _vector) {
        f(element);
    }
}

template <class T>
void STVector<T>::swapElement(size_t pos, T *other) {
    std::lock_guard<std::mutex> guard(_mutex);
    std::swap(_vector[pos], other);
}

template <class T>
void STVector<T>::swap(STVector<T> &other) {
    std::lock_guard<std::mutex> guard(_mutex);
    _vector.swap(other._vector);
}

#endif //STVECTOR_STVECTOR_H
