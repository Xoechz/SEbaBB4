#include "baseclass.h"
#include <iostream>

template <typename T>
class derivedclass : public baseclass<T>
{
    friend std::ostream& operator<<(std::ostream& os, const derivedclass<T>& obj)
    {
        for (int i = 0; i < obj._currentIndex; ++i)
        {
            os << obj._data[i] << " "; // Access _data directly since it's a friend
        }

        return os;
    }

private:
    T* _data;
    int _currentIndex;

public:
    // Constructor calls base constructor with size parameter and initializes _currentIndex
    derivedclass(int size = 10) : baseclass<T>(size), _currentIndex(0)
    {
        // Allocate memory for _data based on the size provided
        _data = new T[size];
    }

    // Destructor to clean up allocated memory
    virtual ~derivedclass()
    {
        delete[] _data; // Free the allocated memory for _data
    }

    // copy constructor to create a deep copy of the derivedclass
    derivedclass(const derivedclass& other) : baseclass<T>(other.getSize()), _currentIndex(other._currentIndex)
    {
        // Allocate memory for _data and copy the values from the other instance
        _data = new T[other.getSize()];
        for (int i = 0; i < other.getSize(); ++i)
        {
            _data[i] = other._data[i];
        }
    }

    // move constructor to transfer ownership of resources
    derivedclass(derivedclass&& other) noexcept : baseclass<T>(other.getSize())
    {
        // Transfer ownership of the data pointer and current index from the other instance
        _data = other._data;
        _currentIndex = other._currentIndex;

        // Set the other instance's data pointer to nullptr to avoid double deletion
        other._data = nullptr;
        other._currentIndex = 0; // Reset the index of the moved-from instance
    }

    // copy assignment operator to create a deep copy of the derivedclass
    derivedclass& operator=(const derivedclass& other)
    {
        if (this != &other) // Check for self-assignment
        {
            // Clean up existing resources
            delete[] _data;

            // Allocate new memory and copy the values from the other instance
            _data = new T[other.getSize()];
            for (int i = 0; i < other.getSize(); ++i)
            {
                _data[i] = other._data[i];
            }

            _currentIndex = other._currentIndex;
        }

        return *this;
    }

    // move assignment operator to transfer ownership of resources
    derivedclass& operator=(derivedclass&& other) noexcept
    {
        if (this != &other) // Check for self-assignment
        {
            // Clean up existing resources
            delete[] _data;

            // Transfer ownership of the data pointer and current index from the other instance
            _data = other._data;
            _currentIndex = other._currentIndex;

            // Set the other instance's data pointer to nullptr to avoid double deletion
            other._data = nullptr;
            other._currentIndex = 0; // Reset the index of the moved-from instance
        }

        return *this;
    }

    // Override getValue to return the value at the current index
    virtual T getValue(int index) const override
    {
        if (index < 0 || index >= this->getSize())
        {
            throw std::out_of_range("Index out of range");
        }

        return _data[index];
    }

    // Override operator[] to provide access to the value at the current index
    virtual T operator[](int index) const override
    {
        return getValue(index); // Use getValue to access the value at the index
    }

    // Override addValue to add a value at the current index and increment the index
    virtual void addValue(T value) override
    {
        if (_currentIndex < 0 || _currentIndex >= this->getSize())
        {
            throw std::out_of_range("Index out of range");
        }

        _data[_currentIndex] = value; // Store the value at the current index
        _currentIndex++; // Increment the index for the next value
    }

    // Override operator+= to add a value at the current index and increment the index
    virtual void operator+=(T value) override
    {
        addValue(value); // Use addValue to handle the addition and index increment
    }

    class iterator
    {
    private:
        T* _ptr; // Pointer to the data
        int _index; // Current index in the data array

    public:
        // Constructor to initialize the iterator with a pointer
        iterator(T* ptr, int index) : _ptr(ptr), _index(index) {}

        // Overload the dereference operator to return the value at the current index
        T& operator*() const
        {
            return _ptr[_index];
        }

        // Overload the increment operator to move to the next index
        iterator& operator++()
        {
            _index++;
            return *this;
        }

        // Overload the equality operator to compare two iterators
        bool operator==(const iterator& other) const
        {
            return _index == other._index && _ptr == other._ptr;
        }

        // Overload the inequality operator to compare two iterators
        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

    };

    iterator begin()
    {
        return iterator(_data, 0); // Return an iterator pointing to the start of the data
    }

    iterator end()
    {
        return iterator(_data, _currentIndex); // Return an iterator pointing to the end of the data
    }
};
