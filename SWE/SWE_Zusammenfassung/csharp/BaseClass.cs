namespace demo;

public abstract class BaseClass<T>(int size) : IInterface<T>
{
    private readonly int _size = size;

    public int Size => _size; // readonly property for size

    // the interface methods need to be mentioned in the abstract class
    public abstract T GetValue(int index); 

    public abstract void AddValue(T value);

    public abstract T this[int index] { get; }
}