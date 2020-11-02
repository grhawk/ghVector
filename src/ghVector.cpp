#ifndef GH_VECTOR_ONCE_H
#define GH_VECTOR_ONCE_H

#include <string>
#include <iostream>

namespace ghds {
    typedef unsigned int uint;

    template<typename T>
    class Vector {
    private:
        uint m_size = 0;
        uint m_capacity = 2;
        T* m_array;

    public:

        Vector() {
            m_array = (T*) ::operator new(m_capacity * sizeof(T));
//            for(size_t i = 0; i < m_capacity; i++)
//                m_array[i] = T();
        }

        explicit Vector(T value) {
            m_array = (T*) ::operator new(m_capacity * sizeof(T));
//            for(size_t i = 0; i < m_capacity; i++)
//                m_array[i] = T();
            push_back(value);
        }

        T& operator[](ghds::uint i) {
            return m_array[i];
        }

        ~Vector() {
            Clear();
            ::operator delete[](m_array);
        }

        uint size() const noexcept {
            return m_size;
        }

        void push_back(const T& value) noexcept {
            if (m_size < m_capacity) {
                m_array[m_size] = T(value);
                m_size++;
            } else {
                ghds::uint new_capacity = computeNewCapacity();
                reallocate(new_capacity);
                m_array[m_size] = T(value);
                m_size++;
            }
        }

        void push_back(T&& value) noexcept {
            if (m_size < m_capacity) {
                m_array[m_size] = std::move(value);
                m_size++;
            } else {
                ghds::uint new_capacity = computeNewCapacity();
                reallocate(new_capacity);
                m_array[m_size] = std::move(value);
                m_size++;
            }
        }

        T operator[](ghds::uint i) const {
            return m_array[i];
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
            T* new_array = (T*) ::operator new(new_capacity * sizeof(T));
            for (ghds::uint i = 0; i < position; i++)
                new_array[i] = std::move(m_array[i]);
            new_array[position] = value;
            m_size++;
            for (ghds::uint i = (position + 1); i < m_size; i++)
                new_array[i] = std::move(m_array[i - 1]);

            ::operator delete[](m_array);
            m_array = new_array;
            m_capacity = new_capacity;
        }

        void shrink_to_fit() {
            if (m_size == m_capacity)
                return;
            reallocate(m_size);
        }

        void Clear() noexcept {
            for (size_t i = 0; i < m_size; i++){
                m_array[i].~T();
            }
            m_size = 0;
        }

        void pop_back() {
            if (m_size == 0)
                return;
            m_size--;
            m_array[m_size].~T();
        }

    private:
        uint computeNewCapacity() const {
            //return m_capacity + 1;
            return this->m_capacity + (this->m_capacity / 2);;
        }

        void reallocate(uint new_capacity) {
            T* new_array = (T*) ::operator new(new_capacity * sizeof(T));
            for (uint i = 0; i < m_size; i++) {
                new_array[i] = std::move(m_array[i]);
            }

            for (size_t i = 0; i < m_size; i++){
                m_array[i].~T();
            }

            ::operator delete[](m_array);
            m_capacity = new_capacity;
            m_array = new_array;
        }


    };
}

#endif