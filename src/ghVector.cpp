#include "ghVector.h"

template<typename T>
int ghds::Vector<T>::size() const {
    return m_size;
}

template<typename T>
void ghds::Vector<T>::push_back(T value) {
    m_size++;
}


template class ghds::Vector<int>;