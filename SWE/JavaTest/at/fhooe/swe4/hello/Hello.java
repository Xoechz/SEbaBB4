package at.fhooe.swe4.hello;

public class Hello{
    public void sayHello() {
        System.out.println("Hello, World!");
    }

    public static void main(String[] args) {
        Hello hello = new Hello();
        hello.sayHello();
    }
}