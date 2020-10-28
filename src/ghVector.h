#ifndef GH_VECTOR_ONCE_H
#define GH_VECTOR_ONCE_H

namespace ghds {
    typedef unsigned int uint;
    
    template <typename T>
    class Vector {
    public:
        Vector();
        ~Vector();
        uint size() const noexcept;
        void push_back(T value) noexcept;
        T operator[](uint i) const;
        T& operator[](uint i);
        void insert(uint position, T value);
        ghds::uint capacity() const noexcept;

    private:
        uint m_size = 0;
        uint m_capacity = 2;
        T* m_array;

    private:
        uint computeNewCapacity() const;
    };

}
#endif