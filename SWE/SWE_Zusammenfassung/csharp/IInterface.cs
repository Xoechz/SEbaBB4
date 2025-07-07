namespace demo;

// C# supports interfaces and generics and operator overloading(only indexers are supported in interfaces)
public interface IInterface<T>
{
    T GetValue(int index);

    void AddValue(T value);

    T this[int index] { get; }
}
