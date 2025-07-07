using System.Collections;
using System.Text;

namespace demo;

// IEnumerable is commonly used for iteration in C#, but it is not required because forEach can be used with any class that implements GetEnumerator(Duck Typing).
public class DerivedClass<T> : BaseClass<T>, IEnumerable<T>
{
    private readonly T[] data;
    private int currentIndex;

    // could also be a primary constructor like in the base class
    public DerivedClass(int size) : base(size)
    {
        data = new T[size];
        currentIndex = 0;
    }

    public override T GetValue(int index)
    {
        if (index < 0 || index >= Size)
        {
            throw new IndexOutOfRangeException();
        }

        return data[index];
    }

    public override void AddValue(T value)
    {
        if (currentIndex < 0 || currentIndex >= Size)
        {
            throw new IndexOutOfRangeException();
        }

        data[currentIndex++] = value;
    }

    // C# supports indexers
    public override T this[int index]
    {
        get { return GetValue(index); }
    }

    public static DerivedClass<T> operator +(DerivedClass<T> obj, T value)
    {
        obj.AddValue(value);
        return obj;
    }

    public override string ToString()
    {
        var stringBuilder = new StringBuilder();

        for (int i = 0; i < currentIndex; i++)
        {
            stringBuilder.Append($"{data[i]} ");
        }

        return stringBuilder.ToString().Trim();
    }

    public IEnumerator<T> GetEnumerator()
    {
        for (int i = 0; i < currentIndex; i++)
        {
            yield return data[i];
        }
    }

    // The non-generic version of GetEnumerator needs to be implemented explicitly
    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }

    // No need for destructors or manual memory management
}
