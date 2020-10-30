#ifndef GH_VECTOR_ONCE_H
#define GH_VECTOR_ONCE_H

#include <string>

namespace ghds {
    typedef unsigned int uint;

    template<typename T>
    class Vector {
    private:
        uint m_size = 0;
        uint m_capacity = 2;
        T* m_array;

    public:

        uint size() const noexcept {
            return m_size;
        }

        void push_back(T value) noexcept {
            if (m_size < m_capacity) {
                m_array[m_size] = value;
                m_size++;
            } else {
                ghds::uint new_capacity = computeNewCapacity();
                T* new_array = new T[new_capacity];
                std::memcpy(new_array, m_array, m_size * sizeof(T));
                for (ghds::uint i = 0; i < m_size; i++) {
                    new_array[i] = m_array[i];
                }
                delete[] m_array;
                m_capacity = new_capacity;
                m_array = new_array;
                m_array[m_size] = value;
                m_size++;
            }
        }

        T operator[](ghds::uint i) const {
            return m_array[i];
        }

        Vector()
                : m_array{new T[m_capacity]} {
        }

        Vector(T value) {
            m_array = new T[m_capacity];
            push_back(value);
        }

        T& operator[](ghds::uint i) {
            return m_array[i];
        }

        ~Vector() {
            delete[] m_array;
        }

        uint capacity() const noexcept {
            return m_capacity;
        }

        void insert(ghds::uint position, T value) {
            if (position >= m_size)
                throw std::exception();
            ghds::uint new_capacity = m_capacity;
            if (m_size == m_capacity)
                new_capacity = computeNewCapacity();
            T* new_array = new T[new_capacity];
            std::memcpy(new_array, m_array, (position) * sizeof(T));
            new_array[position] = value;
            m_size++;
            std::memcpy(&new_array[position + 1], &m_array[position], (m_size - position) * sizeof(T));

            delete[] m_array;
            m_array = new_array;
            m_capacity = new_capacity;
        }

    private:
        uint computeNewCapacity() const {
            return this->m_capacity + (this->m_capacity / 2);;
        }

    };
}

#endif