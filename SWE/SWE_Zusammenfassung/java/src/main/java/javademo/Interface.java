package javademo;

// Java supports interfaces and generics but not operator overloading
public interface Interface<T> {
    T getValue(int index);

    void addValue(T value);

    int getSize();
    // No operator[] or operator+= in Java
}
