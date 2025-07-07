package javademo;

public abstract class BaseClass<T> implements Interface<T> {
    private int size;

    BaseClass(int size) {
        this.size = size;
    }

    @Override
    public int getSize() {
        return size;
    }

    // Java supports not implementing interfaces in abstract classes
}
