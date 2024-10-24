#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr
{
public:
    UniquePtr();
    UniquePtr(T *p);
    ~UniquePtr();
    UniquePtr(UniquePtr &ptr) = delete;
    T *get();
    T &operator*();
    T *operator->();
    UniquePtr<T> &operator=(UniquePtr &ptr) = delete;
    void reset();
    void reset(T *p);
    T *release();
    explicit operator bool();

private:
    T *_p;
};

template <typename T>
UniquePtr<T> make_unique(T p)
{
    return UniquePtr<T>{new T{p}};
}

#include "unique_ptr.hpp"
#endif // UNIQUE_PTR