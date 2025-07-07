namespace demo;

static class Program
{
    static void Main()
    {
        var myDerived = new DerivedClass<int>(5);
        myDerived.AddValue(10);
        myDerived.AddValue(20);
        myDerived += 30; // Using operator overloading

        Console.WriteLine($"Value at index 0: {myDerived[0]}");
        Console.WriteLine($"Value at index 1: {myDerived[1]}");
        Console.WriteLine($"Value at index 2: {myDerived.GetValue(2)}");

        Console.WriteLine($"ToString: {myDerived}"); // ToString is called implicitly

        // Iteration using foreach
        Console.Write("Iterating through values: ");
        foreach (var value in myDerived)
        {
            Console.Write($"{value} ");
        }
        Console.WriteLine();
    }
}
