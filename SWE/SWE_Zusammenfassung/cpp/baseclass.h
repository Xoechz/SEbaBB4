#include "interface.h"

template <typename T>
class baseclass : public interface<T>
{
private:
    int _size;

public:
    baseclass(int size = 10) : _size(size) {}// Constructor with default parameter

    virtual int getSize() const override
    {
        return _size;
    }
};