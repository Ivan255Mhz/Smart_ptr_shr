
#include <iostream>

template <typename T>
class SmartPtr {

    T* m_ptr;
    size_t* m_count;
    
    
    void release() {
        if (--(*m_count) == 0) {
            delete m_ptr;
            delete m_count;
        }
    }

public:
    SmartPtr(T* ptr = nullptr) : m_ptr(ptr), m_count(new size_t(ptr != nullptr ? 1 : 0)) {}

    SmartPtr(const SmartPtr& other) : m_ptr(other.m_ptr), m_count(other.m_count) {
        ++(*m_count);
    }

    SmartPtr& operator=(const SmartPtr& other) {
        if (this != &other) {
            release();
            m_ptr = other.m_ptr;
            m_count = other.m_count;
            ++(*m_count);
        }
        return *this;
    }

    ~SmartPtr() {
        release();
    }

    T& operator*() const {
        return *m_ptr;
    }

    T* operator->() const {
        return m_ptr;
    }

    size_t use_count() const {
        return *m_count;
    }


};



int main()
{
    SmartPtr<int> ptr1(new int(42));
    std::cout << "ptr1 use count: " << ptr1.use_count() << std::endl; 

    SmartPtr<int> ptr2 = ptr1;
    std::cout << "ptr1 use count: " << ptr1.use_count() << std::endl; 
    std::cout << "ptr2 use count: " << ptr2.use_count() << std::endl; 

    *ptr2 = 24;
    std::cout << "*ptr1: " << *ptr1 << std::endl; 
    std::cout << "*ptr2: " << *ptr2 << std::endl; 

    return 0;
    
}

