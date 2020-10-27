#ifndef GH_VECTOR_ONCE_H
#define GH_VECTOR_ONCE_H

namespace ghds {

    template <typename T>
    class Vector {
    public:
        int size() const;
        void push_back(T value);
    private:
        int m_size = 0;
    };

}
#endif