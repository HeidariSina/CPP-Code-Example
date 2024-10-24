// Constructor
template <typename T>
UniquePtr<T>::UniquePtr() : _p{nullptr} {};

// Constructor
template <typename T>
UniquePtr<T>::UniquePtr(T *p) : _p{p} {}

// Destructor
template <typename T>
UniquePtr<T>::~UniquePtr()
{
    delete _p;
    _p = nullptr;
}

// Copy
// template <typename T>
// UniquePtr<T>::UniquePtr(UniquePtr<T> &ptr)
// {
//     _p = ptr._p;
// }

// Get
template <typename T>
T *UniquePtr<T>::get()
{
    return _p;
}

// OP *
template <typename T>
T &UniquePtr<T>::operator*()
{
    return (*_p);
}

// OP =
// template <typename T>
// UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr<T> &ptr)
// {
//     if (this == &ptr)
//         return *this;
//     delete _p;
//     _p = ptr._p;
//     return *this;
// }

// OP ->
template <typename T>
T *UniquePtr<T>::operator->()
{
    return _p;
}

// Reset
template <typename T>
void UniquePtr<T>::reset()
{
    delete _p;
    _p = nullptr;
}

// Reset 2
template <typename T>
void UniquePtr<T>::reset(T *p)
{
    delete _p;
    _p = p;
}

// Release
template <typename T>
T *UniquePtr<T>::release()
{
    T *ptr{_p};
    _p = nullptr;
    return ptr;
}

// Bool Op
template <typename T>
UniquePtr<T>::operator bool()
{
    if (_p == nullptr)
        return false;
    return true;
}