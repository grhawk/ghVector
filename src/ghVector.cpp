#include "ghVector.h"

template<typename T>
ghds::uint ghds::Vector<T>::size() const {
    return m_size;
}

template<typename T>
void ghds::Vector<T>::push_back(T value) {
    if (m_size < m_capacity) {
        m_array[m_size] = value;
        m_size++;
    } else {
        ghds::uint new_capacity = m_capacity + (m_capacity / 2);
        T* new_array = new T[new_capacity];
        for (ghds::uint i = 0; i < m_size; i++){
            new_array[i] = m_array[i];
        }
        delete [] m_array;
        m_capacity = new_capacity;
        m_array = new_array;
        m_array[m_size] = value;
        m_size++;
    }
}

template<typename T>
T ghds::Vector<T>::operator[](ghds::uint i) const {
    return m_array[i];
}

template<typename T>
ghds::Vector<T>::Vector()
        : m_array{new T[m_capacity]}
{
}

template<typename T>
T &ghds::Vector<T>::operator[](ghds::uint i) {
    return m_array[i];
}

template<typename T>
ghds::Vector<T>::~Vector() {
    delete[] m_array;
}

template<typename T>
ghds::uint ghds::Vector<T>::capacity() {
    return m_capacity;
}

template<typename T>
void ghds::Vector<T>::insert(ghds::uint position, T value) {
    ghds::uint new_capacity = m_capacity;
    if(m_size == m_capacity){
        new_capacity = m_capacity + (m_capacity / 2);
    }
    T* new_array = new T[new_capacity];
    for(ghds::uint i = 0; i < position; i++)
        new_array[i] = m_array[i];
    new_array[position] = value;
    m_size++;
    for (ghds::uint i = (position+1); i < m_size; i++)
        new_array[i] = m_array[i-1];

    delete [] m_array;
    m_array = new_array;
    m_capacity = new_capacity;
}


template class ghds::Vector<int>;