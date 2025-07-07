package javademo;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class DerivedClass<T> extends BaseClass<T> implements Iterable<T> {
    private ArrayList<T> data;
    private int currentIndex;

    public DerivedClass(int size) {
        super(size);
        data = new ArrayList<>(size); // generic arrays in Java are semi-supported
        currentIndex = 0;
    }

    @Override
    public T getValue(int index) {
        if (index < 0 || index >= getSize()) {
            throw new IndexOutOfBoundsException();
        }

        return data.get(index);
    }

    @Override
    public void addValue(T value) {
        if (currentIndex < 0 || currentIndex >= getSize()) {
            throw new IndexOutOfBoundsException();
        }

        data.add(value);
        currentIndex++;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < currentIndex; i++) {
            sb.append(data.get(i));
            sb.append(" ");
        }

        return sb.toString().trim();
    }

    // Iterable implementation for for-each loop
    @Override
    public Iterator<T> iterator() {
        return new Iterator<T>() {
            private int index = 0;

            @Override
            public boolean hasNext() {
                return index < currentIndex;
            }

            @Override
            public T next() {
                if (!hasNext()) {
                    throw new NoSuchElementException();
                }

                return data.get(index++);
            }
        };
    }

    // No operator overloading in Java, so no operator[] or operator+=
    // No need for destructors or manual memory management
}
