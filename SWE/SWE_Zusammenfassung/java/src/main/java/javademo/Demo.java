package javademo;

public class Demo {
    public static void main(String[] args) {
        DerivedClass<Integer> myDerived = new DerivedClass<>(5);
        myDerived.addValue(10);
        myDerived.addValue(20);
        myDerived.addValue(30);

        System.out.println("Value at index 0: " + myDerived.getValue(0));
        System.out.println("Value at index 1: " + myDerived.getValue(1));
        System.out.println("Value at index 2: " + myDerived.getValue(2));

        System.out.println("toString: " + myDerived.toString());

        System.out.print("Iterating through values: ");
        for (int value : myDerived) {
            System.out.print(value + " ");
        }
        System.out.println();
    }
}
