template <typename T> // Generic programming with templates
class interface // in C++ there is no special keyword for interfaces, so we use a class
{
public:
    virtual ~interface() = default; // Virtual destructor for proper cleanup of derived classes

    virtual T getValue(int index) const = 0; // Pure virtual function, must be implemented by derived classes
    virtual T operator[](int index) const = 0; // operator overload for indexing, must be implemented by derived classes
    virtual void addValue(T value) = 0; // Pure virtual function, must be implemented by derived classes
    virtual void operator+=(T value) = 0; // operator overload for adding a value, must be implemented by derived classes
    virtual int getSize() const = 0; // Pure virtual function, must be implemented by derived classes
};
