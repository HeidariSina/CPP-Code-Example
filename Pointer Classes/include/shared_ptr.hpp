// Constructor
template <typename T>
SharedPtr<T>::SharedPtr() : _p{nullptr}, cnt{new int(0)} {};

// Constructor
template <typename T>
SharedPtr<T>::SharedPtr(T *p) : _p{p}, cnt{new int(1)} {}

// Destructor
template <typename T>
SharedPtr<T>::~SharedPtr()
{
    (*cnt)--;
    if (*cnt == 0)
    {
        if (nullptr != _p)
        {
            delete _p;
            _p = nullptr;
        }
    }
}

// Copy
template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &ptr)
{
    _p = ptr._p;
    cnt = ptr.cnt;
    (*cnt)++;
}

// Get
template <typename T>
T *SharedPtr<T>::get()
{
    return _p;
}

// OP *
template <typename T>
T &SharedPtr<T>::operator*()
{
    return (*_p);
}

// OP =
template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(SharedPtr<T> &ptr)
{
    if (this == &ptr)
        return *this;
    delete _p;
    _p = ptr._p;
    cnt = ptr.cnt;
    (*cnt)++;
    return *this;
}

// OP ->
template <typename T>
T *SharedPtr<T>::operator->()
{
    return _p;
}

// Reset
template <typename T>
void SharedPtr<T>::reset()
{
    delete _p;
    _p = nullptr;
    *cnt = 0;
}

// Reset 2
template <typename T>
void SharedPtr<T>::reset(T *p)
{
    delete _p;
    _p = p;
    *cnt = 1;
}

// Bool Op
template <typename T>
SharedPtr<T>::operator bool()
{
    if (_p == nullptr)
        return false;
    return true;
}

// use_count
template <typename T>
int SharedPtr<T>::use_count()
{
    return *cnt;
}