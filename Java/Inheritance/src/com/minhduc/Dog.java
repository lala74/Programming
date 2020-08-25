package com.minhduc;

public class Dog extends Animal {

    public Dog(String name, int size, int weight) {
        super(name, 1, 1, size, weight);
    }

    public void bark() {
        System.out.println("Dog is barking");
    }

    @Override
    public void eat() {
        System.out.println("Dog is eating");
        bark();
        super.eat();
    }

    @Override
    public void move(int speed) {
        System.out.println("Dog is moving at " + speed + " km/h");
        super.move(speed);
    }

    public void walk() {
        System.out.println("Dog is walking");
        move(5);
    }
}
